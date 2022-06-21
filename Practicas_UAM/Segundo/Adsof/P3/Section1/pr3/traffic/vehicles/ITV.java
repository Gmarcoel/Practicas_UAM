package pr3.traffic.vehicles;

import java.time.*;


/**
 * This is a class that contains the information of a ITV inspection
 * 
 * @author Guillermo Martin-Coello and Daniel Varela
 */
public class ITV {
    LocalDate inspectionDate;
    Garage garage;
    String comments;

    /**
     * This function provides a constructor for the class ITV
     * @param year
     * @param month
     * @param day
     * @param garage
     * @param comments
     */
    public ITV(int year, int month, int day, Garage garage, String comments){
        this.inspectionDate=LocalDate.of(year, month, day);
        this.garage=garage;
        this.comments=comments;
    }

    /**
     * This function returns the year of the last ITV inspection
     * @return year of the last ITV inspection
     */
    public int getYear(){
        return this.inspectionDate.getYear();
    }


    /**
     * This function returns the month of the last ITV inspection
     * @return month of the last ITV inspection
     */
    public int getMonth(){
        return this.inspectionDate.getMonthValue();
    }
    

    /**
     * This function allows printing an ITV
     */
     @Override
     public String toString()
    {
        return "Date " + this.inspectionDate + " garage: " + this.garage + " comments " + this.comments;
    }
}
