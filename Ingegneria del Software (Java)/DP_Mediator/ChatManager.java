import java.util.Date;

public class ChatManager implements ChatManagerInterface {

    private MessagePrinter mp = new MessagePrinter();

    public void showMessage(User user, String message){
        mp.print(new Date().toString() + " [ " + user.getName() + " ] : " + message);
    }

}