package pr3.traffic.drivers;

import pr3.traffic.vehicles.*;
import java.util.*;

/**
 * This is a class for the User attributes
 * 
 * @author Guillermo Martin-Coello and Daniel Varela
 */
public abstract class User {
    private String name;
    private List<Vehicle> vehicles;

    /**
     * This function serves as a constructor of the class User
     * 
     * @param name the name of the User object
     */
    public User(String name) {
        this.name = name;
        this.vehicles = new ArrayList<>();
    }

    /**
     * Function that adds a vehicle ownership to a user
     * 
     * @param vehicle the vehicle owned by the user
     */
    public void addVehicle(Vehicle vehicle) {
        this.vehicles.add(vehicle);
    }

    /**
     * Gives the name of the user
     * 
     * @return The name of the user
     */
    public String getName() {
        return this.name;
    }

    /**
     * Function to print User information
     * 
     * @return It returns the information you need to print when the User is of type
     *         User, including all the owned vehicles if any
     */
    @Override
    public String toString() {
        if (vehicles.isEmpty() == false) {
            String total = "owner of: ";
            for (Vehicle e : vehicles) {
                total = total + "\n" + e.toString();
            }
            return total;
        } else {
            return "";
        }
    }
}
