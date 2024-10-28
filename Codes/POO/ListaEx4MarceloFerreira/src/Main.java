import java.math.BigDecimal;

public class Main {
    public static void main(String[] args) {
        ContaCorrente contaC = new ContaCorrente("Cliente Corrente", "12345",new BigDecimal( 1000), new BigDecimal(1000));
        ContaPoupanca contaP = new ContaPoupanca("Cliente poupanca", "12345",new BigDecimal( 1000), 1);
        ContaInvestimento contaI = new ContaInvestimento("Cliente Investimento", "12345",new BigDecimal( 1000));
        System.out.println("==================================================================");
        System.out.println("Contas Cadastradas:");
        System.out.println(contaC.cliente + " " + contaC.numeroConta + " Saldo = " + contaC.saldo + " Limite = " + contaC.limite);
        System.out.println(contaP.cliente + " " + contaP.numeroConta + " Saldo = " + contaP.saldo + " Rendimento = " + contaP.diaRendimento);
        System.out.println(contaI.cliente + " " + contaI.numeroConta + " Saldo = " + contaI.saldo);
        System.out.println("==================================================================");

        System.out.println("Sacando 100 de contas...");
        contaC.sacar(new BigDecimal(100));
        contaP.sacar(new BigDecimal(100));
        contaI.sacar(new BigDecimal(100));
        System.out.println("Saldo apos sacar:");
        System.out.println(contaC.cliente + " " + contaC.saldo);
        System.out.println(contaP.cliente + " " + contaP.saldo);
        System.out.println(contaI.cliente + " " + contaI.saldo);
        System.out.println("==================================================================");


        System.out.println("Atualizando poupanca com taxa de 0.5...");
        contaP.calcularNovoSaldo(new BigDecimal(0.5));
        System.out.println("Saldo apos Atualizar:");
        System.out.println(contaP.cliente + " " + contaP.saldo);
        System.out.println("==================================================================");

        System.out.println("Depositando 100 em contas...");
        contaC.depositar(new BigDecimal(100));
        contaP.depositar(new BigDecimal(100));
        contaI.depositar(new BigDecimal(100));
        System.out.println("Saldo apos Depositar:");
        System.out.println(contaC.cliente + " " + contaC.saldo);
        System.out.println(contaP.cliente + " " + contaP.saldo);
        System.out.println(contaI.cliente + " " + contaI.saldo);
        System.out.println("==================================================================");

        System.out.println("Calculando tributos da conta com taxa de 1...");
        System.out.println("Tributo calculado = " + contaI.calcularTributo(new BigDecimal(1)));
        System.out.println("==================================================================");

        System.out.println("Calculando a taxa de administração de uma conta investimento com taxa de 1...");
        System.out.println("Taxa calculada = " + contaI.calcularTaxaAdministração(new BigDecimal(1)));
        System.out.println("==================================================================");

    }
}
