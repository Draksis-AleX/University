public class MainBiglietti {
    private static Posizioni cp = new Posizioni();

    public static void main(String[] args) {
        Posto pos = cp.prendiNumero(0);
        Biglietto b = new Biglietto(pos);
        b.Intesta("Mario");
        System.out.println("Costo " + b.getCosto());

		new Biglietto(cp.prendiNumero(0));
		new Biglietto(cp.prendiNumero(0));
		cp.printPostiOccupati();
    }
}
