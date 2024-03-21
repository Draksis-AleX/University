public class SplitTemp {
    
    private double primaryForce, secondaryForce, mass, delay;

    public double getDistanceTravelled(int time) {
        double result;
        final double primAcc = primaryForce / mass;   //prima assegnazione
        int primaryTime = (int) Math.min(time, delay);
        result = 0.5 * primAcc * primaryTime * primaryTime;
        int secondT = (int) (time - delay);
        if (secondT > 0) {
            double primaryVel = acc * delay;
            final double secondAcc = (primaryForce + secondaryForce) / mass;   //seconda assegnazione
            result += primaryVel * secondT + 0.5 * secondAcc * secondT * secondT;
        }
        return result;
    }

    public double getDistanceTravelled2(int time) {
        double result;
        final int primaryTime = (int) Math.min(time, delay);
        result = 0.5 * primAcc() * primaryTime * primaryTime;
        final int secondT = (int) (time - delay);
        if(secondT > 0) result += getDistanceSecondForce(secondT);
        return result;
    }

    public double primAcc() {
        return primaryForce / mass;
    }

    

}
