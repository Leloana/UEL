import java.security.SecureRandom;
import java.util.ArrayList;
public class Senha{
    static SecureRandom aleatorizador = new SecureRandom();

    static public void novaSenha(ArrayList<Integer> Fila){
        int newSenha = aleatorizador.nextInt(99);
        Fila.add(newSenha);
    }

    static public void novaSenha(ArrayList<Integer> Fila, int number){
        Fila.add(number);
    }

    static public void desistirFila(ArrayList<Integer> Fila, int number){
        Fila.remove((Integer) number);
        System.out.print("\nO usuario de numero "+ number +" cansou de esperar");

    }

    static public void atenderUsuario(ArrayList<Integer> FilaComum,ArrayList<Integer> FilaPreferencial, int[] caso){
        if(caso[0] < 2 && !FilaPreferencial.isEmpty()){
            FilaPreferencial.remove(0);
            System.out.print("\nA fila preferencial andou");
            caso[0] ++;
        }
        else if(!FilaComum.isEmpty()){
            FilaComum.remove(0);
            System.out.print("\nA fila comum andou");
            caso[0] = 0;
        }
    }

    static public void buscarPosicao(ArrayList<Integer> Fila, int number){
        int posicao = Fila.indexOf(number);

        System.out.print("\nO usuario de numero "+ number +" esta na posicao " + posicao);
    }

    static public void imprimirFila(ArrayList<Integer> Fila){
        System.out.print("\nFila Atual: ");
        for(int number: Fila){
            System.out.print(number + " ");
        }
    }

}
