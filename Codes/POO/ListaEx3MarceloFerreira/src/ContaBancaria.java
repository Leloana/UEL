import java.math.BigDecimal;

public class ContaBancaria {
    public String cliente;
    public String numeroConta;
    public BigDecimal saldo;

    public void sacar(BigDecimal valor){
        if(valor.compareTo(this.saldo) <= 0){
            this.saldo = this.saldo.subtract(valor);

        } else {
            System.out.println("não há saldo suficiente");
        }
    }
    public void depositar(BigDecimal valor){
        this.saldo = this.saldo.add(valor);
    }
}
