import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        List<ContaBancaria> contas = new ArrayList<ContaBancaria>();
        Scanner scan = new Scanner(System.in);
        int numero = 0;
        boolean continuar = true;

        while (continuar) {
            System.out.println("==========================================");
            System.out.println("[1] Cadastrar conta");
            System.out.println("[2] Fazer um saque");
            System.out.println("[3] Atualizar a poupança com rendimento");
            System.out.println("[4] Depositar");
            System.out.println("[5] Ver Saldo");
            System.out.println("[6] Calcular tributo");
            System.out.println("[7] Calcular taxa de administração");
            System.out.println("[8] Informacoes contas existentes");
            System.out.println("[0] Sair");
            System.out.println("==========================================");

            System.out.print("Acao: ");
            int entrada = scan.nextInt();

            if (entrada == 1) {
                System.out.print("Nome: ");
                String nome = scan.next();

                System.out.println("==========================================");
                System.out.println("[1] ContaCorrente");
                System.out.println("[2] ContaInverstimento");
                System.out.println("[3] ContaPoupanca");
                System.out.println("==========================================");

                System.out.print("Acao: ");
                int opcao = scan.nextInt();
                ContaBancaria conta = null;

                /* Seleciona o tipo de conta corrente */
                if (opcao == 1) {
                    conta = new ContaCorrente();
                    System.out.print("Limite desejado: ");
                    BigDecimal lim = BigDecimal.valueOf(scan.nextDouble());
                    ((ContaCorrente)conta).setLimite(lim);
                }
                else if (opcao == 2) conta = new ContaInvestimento();
                else if (opcao == 3) conta = new ContaPoupanca();

                if (conta != null) {
                    conta.setCliente(nome);
                    conta.setNumeroConta(Integer.toString(numero));
                    conta.setSaldo(BigDecimal.ZERO);

                    System.out.println("Numero gerado para a conta: " + conta.getNumeroConta());
                    contas.add(conta);

                    numero++;
                }
                System.out.println("Conta criada!!");

            }
            else if (entrada == 2) {
                System.out.print("Valor a sacar: ");
                BigDecimal saque = BigDecimal.valueOf(scan.nextDouble());
                System.out.print("Numero da conta: ");
                String num = scan.next();

                ContaBancaria conta = null;
                Iterator<ContaBancaria> iter = contas.iterator();
                while (iter.hasNext()) {
                    conta = iter.next();
                    if (conta.getNumeroConta().compareTo(num) == 0) break;
                    conta = null;
                }


                if(conta == null) System.out.println("Conta ainda nao registrada");
                else {
                    conta.sacar(saque);
                    System.out.println("Saque realizado!!");
                }
            }
            else if (entrada == 3) {
                System.out.print("Qual seu rendimento: ");
                BigDecimal ren = BigDecimal.valueOf(scan.nextDouble());
                System.out.print("Numero da conta: ");
                String num = scan.next();

                ContaBancaria conta = null;
                Iterator<ContaBancaria> iter = contas.iterator();
                while (iter.hasNext()) {
                    conta = iter.next();
                    if (conta.getNumeroConta().compareTo(num) == 0) break;
                    conta = null;
                }

                if (conta == null) System.out.println("Conta ainda nao registrada");
                else {
                    ((ContaPoupanca)conta).calcularNovoSaldo(ren);
                    System.out.println("Novo saldo calculado!!");
                }
            }
            else if (entrada == 4) {
                System.out.print("Valor do deposito: ");
                BigDecimal saque = BigDecimal.valueOf(scan.nextDouble());
                System.out.print("Numero da conta: ");
                String num = scan.next();

                ContaBancaria conta = null;
                Iterator<ContaBancaria> iter = contas.iterator();
                while (iter.hasNext()) {
                    conta = iter.next();
                    if (conta.getNumeroConta().compareTo(num) == 0) break;
                    conta = null;
                }

                if (conta == null)System.out.println("Conta ainda nao registrada");
                else {
                    conta.depositar(saque);
                    System.out.println("Deposito realizado!!");
                }
            }
            else if (entrada == 5) {
                System.out.print("Numero da conta: ");
                String num = scan.next();

                ContaBancaria conta = null;
                Iterator<ContaBancaria> iter = contas.iterator();
                while (iter.hasNext()) {
                    conta = iter.next();
                    if (conta.getNumeroConta().compareTo(num) == 0) break;
                    conta = null;
                }

                if (conta == null) System.out.println("Conta ainda nao registrada");
                else {
                    System.out.print("Saldo da conta " + conta.getNumeroConta() + ": ");
                    System.out.println(conta.getSaldo());
                    System.out.println("Saldo obtido!!");
                }
            }
            else if (entrada == 6) {
                System.out.print("Informe o rendimento: ");
                BigDecimal ren = BigDecimal.valueOf(scan.nextDouble());
                System.out.print("Numero da conta: ");
                String num = scan.next();

                ContaBancaria conta = null;
                Iterator<ContaBancaria> iter = contas.iterator();
                while (iter.hasNext()) {
                    conta = iter.next();
                    if (conta.getNumeroConta().compareTo(num) == 0) break;
                    conta = null;
                }

                if (conta == null) System.out.println("Conta ainda nao registrada");
                else {
                    System.out.print("Tributo da conta " + conta.getNumeroConta() + ": ");
                    System.out.println(((ContaInvestimento)conta).calcularTributo(ren));
                    System.out.println("Tributo calculado!!");
                }
            }
            else if (entrada == 7) {
                System.out.print("Informe o rendimento: ");
                BigDecimal ren = BigDecimal.valueOf(scan.nextDouble());
                System.out.print("Numero da conta: ");
                String num = scan.next();

                ContaBancaria conta = null;
                Iterator<ContaBancaria> iter = contas.iterator();
                while (iter.hasNext()) {
                    conta = iter.next();
                    if (conta.getNumeroConta().compareTo(num) == 0) break;
                    conta = null;
                }

                if (conta == null)System.out.println("Conta ainda nao registrada");
                else {
                    System.out.print("Taxa de administracao da conta " + conta.getNumeroConta() + ": ");
                    System.out.println(((ContaInvestimento)conta).calcularTaxaAdministracao(ren));
                    System.out.println("Rendimento calculado!!");
                }
            }
            else if(entrada == 8){
                for (ContaBancaria conta:contas) {
                    System.out.println("Nome do cliente: " + conta.getCliente());
                    System.out.println("Numero da conta: " + conta.getNumeroConta());
                    System.out.println("Saldo da conta: " + conta.getSaldo());
                }
            }
            else if (entrada == 0) {
                contas.clear();
                continuar = false;
            }
            else System.out.println("entre com uma opcao valida");
        }
    }
}
