public class Carro {
    public String marca;
    public String modelo;

    public Carro(String marca, String modelo){
        this.marca = marca;
        this.modelo = modelo;
    }

    public int getMarcha(double velocidade){
        if(velocidade < 20){
            return 1;
        }
        else if(velocidade >= 20 && velocidade < 40){
            return 2;
        }
        else if(velocidade >= 40 && velocidade < 60){
            return 3;
        }
        else if (velocidade >= 60 && velocidade < 100) {
            return 4;
        }
        else{
            System.out.println("O carro explodiu");
            return 0;
        }
    }
}
