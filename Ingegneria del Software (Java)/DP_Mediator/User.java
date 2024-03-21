public class User {
    private String name;
    private ChatManagerInterface chatManager = new ChatManager();

    public User() {}

    public User(String name) { this.name = name; }

    public void setName(String name) {this.name = name;}

    public String getName() { return this.name; }

    public void sendMessage(String message) {
        chatManager.showMessage(this, message);
    }
}
