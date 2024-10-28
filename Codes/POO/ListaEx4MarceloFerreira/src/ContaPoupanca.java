import java.lang.reflect.Constructor;
import java.math.BigDecimal;

public class ContaPoupanca implements ContaBancaria{
    String cliente;
    String numeroConta;
    BigDecimal saldo;
    int diaRendimento;

    public ContaPoupanca( String cliente, String numeroConta, BigDecimal saldo, int diaRendimento){
        this.cliente = cliente;
        this.numeroConta = numeroConta;
        this.saldo = saldo;
        this.diaRendimento = diaRendimento;
    }
    public void sacar(BigDecimal valor){
        if (valor.compareTo(this.saldo) <= 0){
            this.saldo = this.saldo.subtract(valor);
        }
    }

    public void depositar(BigDecimal valor) {
        this.saldo = this.saldo.add(valor);
    }
    public void calcularNovoSaldo(BigDecimal taxa) {
        this.saldo = this.saldo.add(this.saldo.multiply(taxa));
    }
}
