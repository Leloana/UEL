import java.math.BigDecimal;

public class ContaCorrente implements ContaBancaria{
    String cliente;
    String numeroConta;
    BigDecimal saldo;
    BigDecimal limite;

    public ContaCorrente( String cliente, String numeroConta, BigDecimal saldo, BigDecimal limite){
        this.cliente = cliente;
        this.numeroConta = numeroConta;
        this.saldo = saldo;
        this.limite = limite;
    }
    public void sacar(BigDecimal valor) {
        if (valor.compareTo(this.saldo) <= 0) {
            this.saldo = this.saldo.subtract(valor);
        } else if (valor.compareTo(this.saldo.add(this.limite)) <= 0) {
            this.saldo = this.saldo.subtract(valor);
        } else {
            System.out.println("não há limite suficiente");
        }
    }

    public void depositar(BigDecimal valor) {
        this.saldo = this.saldo.add(valor);
    }
}
