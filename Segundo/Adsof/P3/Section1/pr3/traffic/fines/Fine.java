package pr3.traffic.fines;

/**
 * This class stores a fine information
 */
public class Fine {
    String plate;
    String type;
    String points;

    /**
     * This function provides a constructor for the Fine class
     */
    public Fine(String plate, String type, String points){
        this.plate=plate;
        this.type=type;
        this.points=points;
    }
    
    /**
     * This function returns the points that will be removed by the fine
     * @return String with the points removed
     */
    public String getPoints() {
        return this.points;
    }
    
    /**
     * This function returns the plate number of the vehicle fined
     * @return String with the plate of the vehicle fined
     */
    public String getPlate() {
        return this.plate;
    }

    /**
     * This function allows printing fines
     */
    @Override
    public String toString() {
        return "Fine [plate=" + this.plate +  ", Fine type=" + this.type + ", points=" + this.points + "]";
    }


}
