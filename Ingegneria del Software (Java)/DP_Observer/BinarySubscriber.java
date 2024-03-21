public class BinarySubscriber implements Subscriber{

    public BinarySubscriber(Publisher publisher){
       publisher.attach(this);
    }
 
    @Override
    public void update(Publisher publisher) {
       System.out.println( "Binary String: " + Integer.toBinaryString( publisher.getState() ) ); 
    }
 }