import java.security.SecureRandom;

public class Main {
    public static void main(String[] args){
        SecureRandom aleatorizador = new SecureRandom();
        int[] contalibidade = new int[6];

         for(int i = 0; i < 20; i++) {
             double valor = aleatorizador.nextDouble(600);

             System.out.println("O valor "+i+" é de "+valor);

             if (valor < 100.00) {
                 contalibidade[0]++;
             }
             else if (valor >= 100.00 && valor < 200.00) {
                 contalibidade[1]++;
             }
             else if (valor >= 200.00 && valor < 300.00) {
                 contalibidade[2]++;
             }
             else if (valor >= 300.00 && valor < 400.00) {
                 contalibidade[3]++;
             }
             else if (valor >= 400.00 && valor < 500.00) {
                 contalibidade[4]++;
             }
             else contalibidade[5]++;
         }

        for (int number : contalibidade) {
            System.out.print(number + " ");
        }
    }
}