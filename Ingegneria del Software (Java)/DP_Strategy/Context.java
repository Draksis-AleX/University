public class Context {
    
    private Strategy str;

    public Context(Strategy str) { this.str = str; }

    public void setStrategy(Strategy str) { this.str = str; }

    public int executeStrategy(int num1, int num2) { 
        return str.doOperation(num1, num2); 
    }

}
