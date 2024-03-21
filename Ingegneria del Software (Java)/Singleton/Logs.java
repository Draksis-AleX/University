import java.util.*;

public class Logs { // Classe Singleton
    private static Logs obj; // obj tiene l’istanza
    private ArrayList<String> l; // tiene i dati da registrare

    private Logs() { // il costruttore è privato
        empty();
    }

    public static Logs getInstance() { // restituisce l’unica istanza
        if (obj == null) obj = new Logs(); // crea l’istanza se non presente
        return obj;
    }

    public void record(String s) { // accoda il dato
        l.add(s);
    }

    public String dumpLast() { // restituisce l’ultimo dato
        return l.getLast();
    }

    public String dumpAll() { // restituisce tutti i dati
        String acc = "";
        for (String s : l) // s tiene ciascun elemento in lista, ad ogni passata
        acc = acc.concat(s);
        return acc;
    }

    public void empty() {
        l = new ArrayList<String>();
    }
}