public class Rectangle {
    private double width = 1;
    private double length = 1;

    public double getLength() {
        return length;
    }

    public void setLength(double length) {
        if(length > 0 && length < 20) this.length = length;
        else System.out.println("Valor de length invalido");
    }

    public double getWidth() {
        return width;
    }

    public void setWidth(double width) {
        if(width > 0 && width < 20) this.width = width;
        else System.out.println("Valor de width invalido");
    }

    public double getArea(){
        return this.length * this.width;
    }

    public double getPerimetro(){
        return (2 * this.width) + (2 * this.length);
    }
}
