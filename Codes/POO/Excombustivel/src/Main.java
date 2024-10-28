// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {
        Bomba um = new Bomba(1);
        Bomba dois = new Bomba(2);
        Bomba tres = new Bomba(3);

        Combustivel gasolina = new Combustivel("gasolina", 5.50);
        Combustivel etanol = new Combustivel("etanol", 4.50);
        Combustivel s10 = new Combustivel("s-10", 6.50);

        um.addCombustiveis(gasolina,etanol);

        dois.combustiveis.add(s10);

        tres.combustiveis.add(etanol);

        um.abasteceDinheiro(11.00, "gasolina");
        um.abasteceLitros(2, "etanol");
    }
}