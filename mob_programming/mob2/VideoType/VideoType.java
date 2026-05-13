package VideoType;

public abstract class VideoType {
    int basePoints;
    double baseCharge;

    public VideoType(int basePoints, double baseCharge) {
        this.basePoints = basePoints;
        this.baseCharge = baseCharge;
    }

    public double getCharge() {
        return baseCharge;
    }

    public int getPoints() {
        return basePoints;
    }
}
