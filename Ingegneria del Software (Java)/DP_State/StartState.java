public class StartState implements State {

    private Context context;

    public StartState(Context context) {
        this.context = context;
    }

    public void doAction() {
        System.out.println("StartState::doAction()");
        State stopped = new StopState(context);
        context.setState(stopped);
    }
}
