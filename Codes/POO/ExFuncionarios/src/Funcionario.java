public class Funcionario {
    public String nome;
    public double salario;

    static public double vale = 100;

    public void mudaVale(double taxa){
        vale *= taxa;
    }
}
