public class Demo {
    public static void main(String[] args) {
        Context context = new Context();
        StartState startState = new StartState(context);
        context.setState(startState);

        context.doAction();

        context.doAction();
    }
}
