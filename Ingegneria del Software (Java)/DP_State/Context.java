public class Context {

    private State state;

    public Context() { 
        state = null; 
    }

    public void setState(State state) { this.state = state; }

    public State getState() { return this.state; }

    public void doAction() { state.doAction(); }
}
