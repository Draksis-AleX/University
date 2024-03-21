import java.util.Set;
import java.util.TreeSet;

public abstract class GnrPosizioni {
    private static final int MAXPOSTI = 100;
    private final Set<String> pst = new TreeSet<>();

    public Posto prendiNumero(int x){
        if(pst.size() >= MAXPOSTI) return null;

        Posto p;
        do {
            p = getPosto(x);
        } while (pst.contains(p.getPosizione()));
        pst.add(p.getPosizione());
        return p;
    }

    public void printPostiOccupati(){
        for (String s : pst) System.out.print(s + "  ");
    }

    public abstract Posto getPosto(int tipo);
}
