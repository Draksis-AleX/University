
public class SostituisciTemp{

    private double quantita, prezzo;

    public double getPrezzo1() {
        return prezzoBase() * sconto();
    }

    public double prezzoBase() {
        return quantita * prezzo;
    }

    public double sconto() {
        if (prezzoBase() > 1000) return 0.95;
        else return 0.98;
    }

}




