// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[]args){
        Rectangle ret = new Rectangle();

        System.out.println(ret.getArea());
        System.out.println(ret.getPerimetro());

        ret.setLength(24);
        ret.setWidth(10);

        System.out.println(ret.getArea());
        System.out.println(ret.getPerimetro());
    }
}