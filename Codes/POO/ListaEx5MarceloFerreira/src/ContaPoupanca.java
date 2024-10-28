import java.math.BigDecimal;

public class ContaPoupanca extends ContaBancaria {

    private int diaRendimento = 1;

    public void sacar (BigDecimal valor) {
        if (valor.compareTo(getSaldo()) <= 0){
            setSaldo(getSaldo().subtract(valor));
        }
        else System.out.println("Nao ha saldo suficiente");
    }

    public void calcularNovoSaldo (BigDecimal taxaRendimento) {
        if (this.diaRendimento == 1) {
            setSaldo(getSaldo().add(getSaldo().multiply(taxaRendimento)));
        }
        else return;
    }
}
