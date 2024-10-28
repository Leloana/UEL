// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {
        if(args.length == 0){
            System.out.println("Nenhum argumento fornecido");
            return;
        }
        int soma = 0;

        for( String num : args){
            soma += Integer.parseInt(num);
        }

        System.out.println(soma);
    }
}