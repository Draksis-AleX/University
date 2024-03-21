public class Demo {
    public static void main(String[] args) {
        AbstractShapeFactory asf = new RoundedShapeFactory();
        Shape s1 = asf.getRectangle();
        Shape s2 = asf.getSquare();
        s1.draw();
        s2.draw();

        asf = new SharpShapeFactory();
        s1 = asf.getRectangle();
        s2 = asf.getSquare();
        s1.draw();
        s2.draw();
    }
}
