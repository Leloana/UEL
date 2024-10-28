import java.math.BigDecimal;

public class ContaInvestimento implements ContaBancaria, Tributavel{
    String cliente;
    String numeroConta;
    BigDecimal saldo;
    public ContaInvestimento( String cliente, String numeroConta, BigDecimal saldo){
        this.cliente = cliente;
        this.numeroConta = numeroConta;
        this.saldo = saldo;
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
    public BigDecimal calcularTaxaAdministração(BigDecimal taxaRendimento){
        BigDecimal rendeu = this.saldo.multiply(taxaRendimento);
        return rendeu.divide(new BigDecimal(100));
    }
    public BigDecimal calcularTributo(BigDecimal taxaRendimento){
        BigDecimal rendeu = this.saldo.multiply(taxaRendimento);
        return rendeu.divide(new BigDecimal(200));
    }

}
