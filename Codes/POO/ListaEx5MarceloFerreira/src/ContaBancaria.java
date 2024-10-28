import java.math.BigDecimal;
import java.security.SecureRandom;

public abstract class ContaBancaria {

    private String cliente;
    private String numeroConta;
    private BigDecimal saldo;

    public String getCliente () {
        return this.cliente;
    }

    public String getNumeroConta () {
        return this.numeroConta;
    }

    public BigDecimal getSaldo () {
        return this.saldo;
    }

    public void setCliente (String cliente) {
        this.cliente = cliente;
    }

    public void setNumeroConta (String numeroConta) {
        this.numeroConta = numeroConta;
    }

    public void setSaldo (BigDecimal saldo) {
        this.saldo = saldo;
    }

    public void depositar (BigDecimal valor) {
        this.saldo = this.saldo.add(valor);
    }

    public abstract void sacar (BigDecimal valor);
}
