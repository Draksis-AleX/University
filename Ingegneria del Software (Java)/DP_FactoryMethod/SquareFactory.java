public class SquareFactory extends ShapeFactory{

    @Override
    public Shape getShape(){
        return new Square();
    }    
}
