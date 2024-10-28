public class Gerente{
    private String nome;
    static public double salarios;
    public Gerente(String nome){
        this.nome = nome;
    }

    public void aumentaSalario(double taxa){
        salarios *= taxa;
    }

    public void aumentaSalario(){
        salarios *= 1.1;
    }
}
