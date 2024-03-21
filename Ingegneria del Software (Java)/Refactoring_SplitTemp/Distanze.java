public class Distanze {
    
    private double primaryForce, secondaryForce, mass, delay;

    Distanze(double primaryForce, double secondaryForce, double mass, double delay) {
        this.primaryForce = primaryForce;
        this.secondaryForce = secondaryForce;
        this.mass = mass;
        this.delay = delay;
    }

    public double getDistanceTravelled(int time) {
        double result;
        final double primAcc = primaryForce / mass;   //prima assegnazione
        int primaryTime = (int) Math.min(time, delay);
        result = 0.5 * primAcc * primaryTime * primaryTime;
        int secondT = (int) (time - delay);
        if (secondT > 0) {
            double primaryVel = primAcc * delay;
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

    public double secondAcc() {
        return (primaryForce + secondaryForce) / mass;
    }

    public double getDistanceSecondForce(double secondT) {
        double primaryVel = primAcc() * delay;
        return primaryVel * secondT + 0.5 * secondAcc() * secondT * secondT;
    }
    

}
