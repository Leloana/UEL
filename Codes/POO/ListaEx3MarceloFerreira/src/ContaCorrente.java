import java.math.BigDecimal;

public class ContaCorrente extends ContaBancaria{
    public BigDecimal limite;

    @Override
    public void sacar(BigDecimal valor){
        if(valor.compareTo(this.saldo) <= 0){
            this.saldo = this.saldo.subtract(valor);

        } else if(valor.compareTo(this.saldo.add(limite)) <= 0) {
            this.saldo = this.saldo.subtract(valor);
        }
           else System.out.println("não há limite suficiente");
    }
}
