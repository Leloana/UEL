import java.security.SecureRandom;

public class Main {
    public static void main(String[] args) {
        SecureRandom random = new SecureRandom();
        int dice = random.nextInt(5);
        Sinaleiro state = Sinaleiro.VERMELHO;

        for(int i = 0; i < 3; i++) {
            System.out.println(dice);
            if (dice < 2) {
                state = Sinaleiro.VERMELHO;
            }
            else if (dice < 4) {
                state = Sinaleiro.AMARELO;
            }
            else state = Sinaleiro.VERDE;

            dice = random.nextInt(5);
        }
        System.out.println(state);
    }
}