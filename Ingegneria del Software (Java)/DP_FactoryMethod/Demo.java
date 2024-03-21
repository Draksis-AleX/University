public class Demo {
    public static void main(String[] args) {
        ShapeFactory sf = new SquareFactory();
        sf.execute();  //Draw indiretto
        Shape myShape = sf.getShape();
        myShape.draw();

        sf = new CircleFactory();
        sf.execute();  //Draw indiretto
        myShape = sf.getShape();
        myShape.draw();     //Draw diretto

        sf = new RectangleFactory();
        sf.execute();  //Draw indiretto
        myShape = sf.getShape();
        myShape.draw();     //Draw diretto

    }
}
