import grpc
from concurrent import futures
import redis
import threading
import bank_pb2
import bank_pb2_grpc

class BankService(bank_pb2_grpc.BankServiceServicer):
    def __init__(self):
        try:
            self.redis = redis.Redis(host='localhost', port=6379, decode_responses=True)
            # Forçar operação real
            self.redis.set("test_connection", "ok", ex=5)  # salva uma chave com expiração
            value = self.redis.get("test_connection")      # lê a chave
            if value != "ok":
                raise redis.exceptions.ConnectionError("Falha na operação de escrita/leitura no Redis.")
        except Exception as e:
            print("[ERRO] Falha na conexão real com o Redis:", str(e))
            exit(1)

        self.lock = threading.Lock()



    def CreateAccount(self, request, context):
        with self.lock:
            if self.redis.exists(request.account_id):
                context.abort(grpc.StatusCode.ALREADY_EXISTS, "Account already exists.")
            account_data = {
                "account_type": request.account_type,
                "balance": 0.0
            }
            self.redis.hmset(request.account_id, account_data)
            return bank_pb2.AccountResponse(
                account_id=request.account_id,
                message="Account created successfully."
            )

    def GetBalance(self, request, context):
        if not self.redis.exists(request.account_id):
            context.abort(grpc.StatusCode.NOT_FOUND, "Account not found. Please check the account ID.")
        balance = float(self.redis.hget(request.account_id, "balance"))
        return bank_pb2.BalanceResponse(
            account_id=request.account_id,
            balance=balance,
            message="Balance retrieved successfully."
        )

    def Deposit(self, request, context):
        if request.amount <= 0:
            context.abort(grpc.StatusCode.INVALID_ARGUMENT, "Transaction amount must be positive.")
        if not self.redis.exists(request.account_id):
            context.abort(grpc.StatusCode.NOT_FOUND, "Account not found. Please check the account ID.")

        with self.lock:
            balance = float(self.redis.hget(request.account_id, "balance"))
            new_balance = balance + request.amount
            self.redis.hset(request.account_id, "balance", new_balance)
            return bank_pb2.TransactionResponse(
                account_id=request.account_id,
                message="Deposit successful.",
                balance=new_balance
            )

    def Withdraw(self, request, context):
        if request.amount <= 0:
            context.abort(grpc.StatusCode.INVALID_ARGUMENT, "Transaction amount must be positive.")
        if not self.redis.exists(request.account_id):
            context.abort(grpc.StatusCode.NOT_FOUND, "Account not found. Please check the account ID.")

        with self.lock:
            balance = float(self.redis.hget(request.account_id, "balance"))
            if balance < request.amount:
                context.abort(grpc.StatusCode.FAILED_PRECONDITION, "Insufficient funds for the requested withdrawal.")
            new_balance = balance - request.amount
            self.redis.hset(request.account_id, "balance", new_balance)
            return bank_pb2.TransactionResponse(
                account_id=request.account_id,
                message="Withdrawal successful.",
                balance=new_balance
            )

    def CalculateInterest(self, request, context):
        if request.annual_interest_rate <= 0:
            context.abort(grpc.StatusCode.INVALID_ARGUMENT, "Annual interest rate must be a positive value.")
        if not self.redis.exists(request.account_id):
            context.abort(grpc.StatusCode.NOT_FOUND, "Account not found. Please check the account ID.")

        with self.lock:
            balance = float(self.redis.hget(request.account_id, "balance"))
            interest = balance * (request.annual_interest_rate / 100)
            new_balance = balance + interest
            self.redis.hset(request.account_id, "balance", new_balance)
            return bank_pb2.TransactionResponse(
                account_id=request.account_id,
                message="Interest calculated and applied successfully.",
                balance=new_balance
            )

def _server():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    bank_pb2_grpc.add_BankServiceServicer_to_server(BankService(), server)
    server.add_insecure_port('[::]:50051')
    print("gRPC Server started on port 50051...")
    server.start()
    server.wait_for_termination()

if __name__ == '__main__':
    _server()
