public class OctalSubscriber implements Subscriber{

    public OctalSubscriber(Publisher publisher){
       publisher.attach(this);
    }
 
    @Override
    public void update(Publisher publisher) {
       System.out.println( "Octal String: " + Integer.toOctalString( publisher.getState() ) ); 
    }
 }