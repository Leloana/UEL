import java.util.ArrayList;
import java.util.Arrays;

public class Bomba {
    public int id;
    public ArrayList<Combustivel> combustiveis;
    public Bomba(int id) {
        this.combustiveis = new ArrayList<>();
    }

    public void addCombustiveis(Combustivel... combustiveis){
        this.combustiveis.addAll(Arrays.asList(combustiveis));
    }
    public void abasteceLitros(double litros, String nomeCombustivel){
        boolean achou = false;
        for (Combustivel combustivel : this.combustiveis) {
            if (combustivel.nome.equalsIgnoreCase(nomeCombustivel)) {
                achou = true;
                System.out.println("O preco sera de " + (combustivel.preco * litros));

            }
        }
        if(!achou) System.out.println("Essa bomba nao possui esse combustivel");
    }

    public void abasteceDinheiro(double dinheiro, String nomeCombustivel){
        boolean achou = false;
        for (Combustivel combustivel : this.combustiveis) {
            if (combustivel.nome.equalsIgnoreCase(nomeCombustivel)) {
                achou = true;
                System.out.println(dinheiro/combustivel.preco + " Litros" );

            }
        }
        if(!achou) System.out.println("Essa bomba nao possui esse combustivel");
    }
}
