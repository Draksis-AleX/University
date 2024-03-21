public abstract class ShapeFactory {
    
    public abstract Shape getShape();

    public void execute(){
        Shape p = this.getShape();
        p.draw();
    }

}
