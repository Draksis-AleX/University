public class RoundedShapeFactory extends AbstractShapeFactory {

    @Override
    public Shape getRectangle() {
        return new RoundedRectangle();
    }

    @Override
    public Shape getSquare() {
        return new RoundedSquare();
    }    
}
