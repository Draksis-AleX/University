public class Demo {
    public static void main(String[] args) {
        User u1 = new User("Mario");
        User u2 = new User("Luigi");

        u1.sendMessage("Ciao Luigi!");
        u2.sendMessage("Ciao Mario...");
    }
}
