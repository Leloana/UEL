import java.math.BigDecimal;

public class ContaInvestimento extends ContaBancaria {

    public void sacar (BigDecimal valor) {
        if (valor.compareTo(getSaldo()) <= 0){
            setSaldo(getSaldo().subtract(valor));
        }
        else System.out.println("Nao ha saldo suficiente");
    }

    public void calcularNovoSaldo (BigDecimal taxaRendimento) {
        setSaldo(getSaldo().add(getSaldo().multiply(taxaRendimento.divide(BigDecimal.valueOf(100)))));
    }

    public BigDecimal calcularTaxaAdministracao (BigDecimal taxaRendimento) {
        BigDecimal taxa = getSaldo().multiply(taxaRendimento).subtract(getSaldo());
        return taxa.divide(BigDecimal.valueOf(100));
    }

    public BigDecimal calcularTributo (BigDecimal taxaRendimento) {
        BigDecimal taxa = getSaldo().multiply(taxaRendimento).subtract(getSaldo());
        return taxa.divide(BigDecimal.valueOf(200));
    }
}
