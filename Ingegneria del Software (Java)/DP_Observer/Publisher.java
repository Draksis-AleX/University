import java.util.List;
import java.util.ArrayList;

public class Publisher {
	
    private List<Subscriber> observers = new ArrayList<Subscriber>();
    private int state;
 
    public int getState() {
       return state;
    }
 
    public void setState(int state) {
       this.state = state;
       notifyAllObservers();
    }
 
    public void attach(Subscriber observer){
       observers.add(observer);		
    }
 
    public void notifyAllObservers(){
       for (Subscriber observer : observers) {
          observer.update(this);
       }
    } 	
 }