public class MainFib {
    public static void main(String[] args) {

        Fib f = Fib.getInstance();
        System.out.print("f " + f.getValue());
        System.out.println(" " + f.getValue());

        Fib f2 = Fib.getInstance();
        System.out.print("f2 " + f2.getValue());
        System.out.println(" " + f2.getValue());

        //  Si avrebbe un errore con:
        //  Fib f3 = (Fib) f2.clone();
        //  Oppure
        //  Fib f4 = new Fib();
    }
}
