import grpc
import bank_pb2
import bank_pb2_grpc

def create_account(stub, account_id, account_type):
    try:
        response = stub.CreateAccount(bank_pb2.AccountRequest(account_id=account_id, account_type=account_type))
        print(f"CreateAccount: {response.message}")
    except grpc.RpcError as e:
        print(f"Error creating account: {e.details()}")

def get_balance(stub, account_id):
    try:
        response = stub.GetBalance(bank_pb2.AccountRequest(account_id=account_id))
        print(f"Balance for account {account_id}: {response.balance}")
    except grpc.RpcError as e:
        print(f"Error retrieving balance: {e.details()}")

def deposit(stub, account_id, amount):
    try:
        response = stub.Deposit(bank_pb2.DepositRequest(account_id=account_id, amount=amount))
        print(f"Deposit: {response.message} - New balance: {response.balance}")
    except grpc.RpcError as e:
        print(f"Error depositing: {e.details()}")

def withdraw(stub, account_id, amount):
    try:
        response = stub.Withdraw(bank_pb2.WithdrawRequest(account_id=account_id, amount=amount))
        print(f"Withdraw: {response.message} - New balance: {response.balance}")
    except grpc.RpcError as e:
        print(f"Error withdrawing: {e.details()}")

def calculate_interest(stub, account_id, annual_interest_rate):
    try:
        response = stub.CalculateInterest(bank_pb2.InterestRequest(account_id=account_id, annual_interest_rate=annual_interest_rate))
        print(f"CalculateInterest: {response.message} - New balance: {response.balance}")
    except grpc.RpcError as e:
        print(f"Error calculating interest: {e.details()}")

def main():
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = bank_pb2_grpc.BankServiceStub(channel)

        create_account(stub, "acc001", "savings")
        deposit(stub, "acc001", 500)
        get_balance(stub, "acc001")
        withdraw(stub, "acc001", 200)
        calculate_interest(stub, "acc001", 5.0)
        get_balance(stub, "acc001")

if __name__ == "__main__":
    main()
