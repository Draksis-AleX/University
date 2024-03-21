public class TestSplitTemp {
    
    public static void main(String[] args){
        Distanze d = new Distanze(2, 1, 2, 2);
        if (d.getDistanceTravelled(3) == d.getDistanceTravelled2(3))
            System.out.println("OK test riuscito");
        else 
            System.out.println("FAILED test fallito");

        if (d.getDistanceTravelled(2) == d.getDistanceTravelled2(2))
            System.out.println("OK test riuscito");
        else 
            System.out.println("FAILED test fallito");
    }

}
