// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args){
        Gerente carlos = new Gerente("carlos");
        Gerente.salarios = 1000;

        carlos.aumentaSalario(1.2);
        System.out.println("Salarios apos aumento de 20%: " + Gerente.salarios);

        carlos.aumentaSalario();
        System.out.println("Salarios apos aumento de mais 10%: " +  Gerente.salarios);
    }
}