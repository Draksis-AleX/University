public class Fib {       // classe che implementa un Singleton

    private static Fib obj;  // istanza di Fib
    private int[] x = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233};
    private int i;

    private Fib() {                       // costruttore privato
        i = 3;
    }

    public static Fib getInstance() {     // metodo della classe
        if (obj == null) obj = new Fib();
        return obj;                       // restituisce l'unica istanza
    }

    public int getValue() {
        if (i < 11) i++;
        return x[i-1];
    }

    public void revert() {
        i = 0;
    }
}