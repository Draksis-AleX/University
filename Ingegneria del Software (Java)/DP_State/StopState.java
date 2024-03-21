public class StopState implements State {

    private Context context;

    public StopState(Context context) {
        this.context = context;
    }

    public void doAction() {
        System.out.println("StopState::doAction()");
    }   
}
