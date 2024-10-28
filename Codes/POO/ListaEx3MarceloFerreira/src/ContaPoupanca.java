import java.math.BigDecimal;

public class ContaPoupanca extends ContaBancaria{
    public int diaRendimento;

    public void calcularNovoSaldo(BigDecimal taxa){
        this.saldo = this.saldo.add(this.saldo.multiply(taxa));
    }
}
