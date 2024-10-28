// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args){
        Funcionario jair = new Funcionario();
        jair.nome = "Jair";
        jair.salario = 1100;


        jair.mudaVale(0.1);
        System.out.println("O vale agora é de " + Funcionario.vale);
    }
}