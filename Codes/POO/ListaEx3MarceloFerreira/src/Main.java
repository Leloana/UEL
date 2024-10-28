import java.math.BigDecimal;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {
        //• Cadastrar a conta (poupança ou corrente) de um cliente;
        ContaPoupanca conta = new ContaPoupanca();
        conta.cliente = "Andrey";

        conta.saldo = new BigDecimal(1000);

        conta.numeroConta = "111";

        conta.diaRendimento = 10;

        //• Sacar um valor da sua conta (poupança ou corrente);
        conta.sacar(new BigDecimal(20));

        //• Atualizar uma conta poupança com o seu rendimento;
        conta.calcularNovoSaldo(new BigDecimal(0.5));

        //• Depositar um determinado valor na conta (poupança ou corrente);
        conta.depositar(new BigDecimal(100));

        //• Mostrar o saldo de uma conta (poupança ou corrente);
        System.out.println("Cliente: " + conta.cliente);
        System.out.println("Conta de numero: " + conta.numeroConta);
        System.out.println("Rendimento diario: " + conta.diaRendimento);
        System.out.println("Saldo atual: " + conta.saldo);

    }
}