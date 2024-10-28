public class Main {
    public static void main(String[] args){

        Carro c = new Carro("Fiat", "UNO");

        double velocidade = 101;
        int marchaAtual = c.getMarcha(velocidade);

        System.out.println("Carro "+ c.marca +" " + c.modelo);
        System.out.println("Marcha atual a " + velocidade + "km é a " + marchaAtual);
    }
}
