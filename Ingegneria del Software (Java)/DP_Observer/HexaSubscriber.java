public class HexaSubscriber implements Subscriber{

    public HexaSubscriber(Publisher publisher){
       publisher.attach(this);
    }
 
    @Override
    public void update(Publisher publisher) {
       System.out.println( "Hex String: " + Integer.toHexString( publisher.getState() ) ); 
    }
 }