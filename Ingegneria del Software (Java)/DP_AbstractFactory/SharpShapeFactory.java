public class SharpShapeFactory extends AbstractShapeFactory {

    @Override
    public Shape getRectangle() {
        return new SharpRectangle();
    }

    @Override
    public Shape getSquare() {
        return new SharpSquare();
    }    
}
