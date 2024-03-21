public class Demo {
    public static void main(String[] args) {
        Context context = new Context(new OperationAdd());		
        System.out.println("10 + 5 = " + context.executeStrategy(10, 5));

        context.setStrategy(new OperationSubtract());		
        System.out.println("10 - 5 = " + context.executeStrategy(10, 5));

        context.setStrategy(new OperationMultiply());	
        System.out.println("10 * 5 = " + context.executeStrategy(10, 5));
    }
}
