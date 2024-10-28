import java.util.ArrayList;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args){
        ArrayList<Integer> FilaComum = new ArrayList<>();
        ArrayList<Integer> FilaPreferencial = new ArrayList<>();
        int[] caso = {0};


        /*inserindo senhas aleatorias*/
        Senha.novaSenha(FilaComum);
        Senha.novaSenha(FilaComum);

        /*inserindo senhas escolhidas*/
        Senha.novaSenha(FilaComum,10);
        Senha.novaSenha(FilaComum, 20);
        Senha.imprimirFila(FilaComum);

        /*inserindo senhas aleatorias*/
        Senha.novaSenha(FilaPreferencial);
        Senha.novaSenha(FilaPreferencial);

        /*inserindo senhas escolhidas*/
        Senha.novaSenha(FilaPreferencial,10);
        Senha.novaSenha(FilaPreferencial, 20);
        Senha.imprimirFila(FilaPreferencial);

        /*Atendendo pessoas*/
        Senha.atenderUsuario(FilaComum, FilaPreferencial, caso);
        Senha.atenderUsuario(FilaComum, FilaPreferencial, caso);
        Senha.atenderUsuario(FilaComum, FilaPreferencial, caso);
        Senha.atenderUsuario(FilaComum, FilaPreferencial, caso);
        Senha.atenderUsuario(FilaComum, FilaPreferencial, caso);
        Senha.atenderUsuario(FilaComum, FilaPreferencial, caso);
        Senha.atenderUsuario(FilaComum, FilaPreferencial, caso);
        Senha.atenderUsuario(FilaComum, FilaPreferencial, caso);
        Senha.atenderUsuario(FilaComum, FilaPreferencial, caso);

        Senha.imprimirFila(FilaPreferencial);
        Senha.imprimirFila(FilaComum);


    }
}