// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args){

        System.out.println(Main.elevaNumeros(2,3));

        System.out.println(Main.menorNumero(3.10,3.20));
    }

    static public double elevaNumeros(int a, int b){
        return Math.pow(a,b);
    }

    static public double menorNumero(double a, double b){
        return Math.min(a,b);
    }
}