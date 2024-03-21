public class Demo {
    public static void main(String[] args) {
        RoundHole hole = new RoundHole(5);
        RoundPeg rpeg = new RoundPeg(5);

        if (hole.fits(rpeg)) System.out.println("Round Peg fits Round Hole");

        SquarePeg sp1 = new SquarePeg(2);
        SquarePeg sp2 = new SquarePeg(20);

        // if (hole.fits(sp1))      non compila perchè RoundHole::fits(RoundPeg) non accetta come paramentro SquarePeg
        // Creo quindi degli adapter

        SquarePegAdapter spa1 = new SquarePegAdapter(sp1);
        SquarePegAdapter spa2 = new SquarePegAdapter(sp2);

        if (hole.fits(spa1)) System.out.println("Round Peg fits Round Hole");
        if (!hole.fits(spa2)) System.out.println("Round Peg DOESN'T fits Round Hole");


    }
}
