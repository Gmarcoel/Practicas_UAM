package pr3.traffic.vehicles;
import java.util.*;
/**
 * This is a class that contains the information of a garage
 * @author Guillermo Martin-Coello and Daniel Varela
 */
public class Garage {
    private String name;
    private String address;
    private String province;
    private ArrayList<Vehicle> vehicles;

    /**
     * This function provides a constructor for the class Garage
     * @param name 
     * @param address
     * @param province
     */
    public Garage(String name, String address, String province)
    {
        this.name = name;
        this.address = address;
        this.province = province;
        this.vehicles = new ArrayList<>();
    }
    /**
     * This function adds a vehicle to the list of vehicles that have passed an ITV in this garage
     * @param vehicle the vehicel added
     */
    public void addVehicle(Vehicle vehicle)  {
        if (this.vehicles.contains(vehicle)) return;
        this.vehicles.add(vehicle);
    }
    
    /**
     * This function returns a list of the vehicles that have passed an ITV in this garage
     * @return the vehicels that have passed an ITV in this garage
     */
    public ArrayList<Vehicle> showVehicles()
    {
        return this.vehicles;
    }

    /**
     * This function allows to print a garage
     */
    @Override
    public String toString()
    {
        return "name: " + this.name + " address: " + this.address + " province: " + this.province;
    }
}
