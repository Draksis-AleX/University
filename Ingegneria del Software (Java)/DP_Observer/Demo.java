public class Demo {
    public static void main(String[] args) {
        Publisher subject = new Publisher();

        new HexaSubscriber(subject);
        new OctalSubscriber(subject);
        new BinarySubscriber(subject);

        System.out.println("First state change: 15");	
        subject.setState(15);
        System.out.println("Second state change: 10");	
        subject.setState(10);
    }
}
