import java.util.ArrayList;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {
        product(2,2,2);
        product(2);
        product(2,2);

        int[] v = {2,2,2,2};

        product(v);

    }

    static void product(int... valores) {
        int total = 1;

        for (int valor : valores) {
            total*=valor;
        }

        System.out.printf("Valor do produto: %d%n", total);
    }
}