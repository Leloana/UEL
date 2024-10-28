import java.math.BigDecimal;

public class ContaCorrente extends  ContaBancaria {

    private BigDecimal limite;

    public BigDecimal getLimite () {
        return this.limite;
    }

    public void setLimite (BigDecimal limite) {
        this.limite = limite;
    }

    public void sacar(BigDecimal valor) {
        if (valor.compareTo(getSaldo()) <= 0) {
            setSaldo(getSaldo().subtract(valor));
        } else if (valor.compareTo(getSaldo().add(this.limite)) <= 0) {
            setSaldo(getSaldo().subtract(valor));
        } else {
            System.out.println("não ha limite suficiente");
        }
    }
}
