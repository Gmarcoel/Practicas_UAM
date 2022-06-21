package pr3.traffic.fines;

import pr3.traffic.vehicles.*;
import pr3.traffic.drivers.*;

import java.util.*;

import java.io.FileWriter;
import java.io.File; // Import the File class
import java.io.IOException; // Import the IOException class to handle errors


/**
 * This class processes a fine
 */
public class FineProcessor {

    private ArrayList<Vehicle> vehicles;

    /**
     * This function provides a constructor to the class FineProcessor
     * 
     * @param vehicleList
     */
    public FineProcessor(List<Vehicle> vehicleList) {
        vehicles = new ArrayList<>();
        vehicles.addAll(vehicleList);
    }

    /**
     * This function processes the fines substracting the necessary points and checking the vehicle's ITV's
     * @param fines the fines that will be processed
     */
    public void process(ArrayList<Fine> fines) {
        Person driver = null;
        int minus;
        int points;
        boolean suspended = false;
        for (Fine f : fines) {
            minus = Integer.parseInt(f.getPoints());
            for (Vehicle v : vehicles) {
                if (v.getPlate().equals(f.getPlate())) {
                    if (v.checkITV() == false) {
                        minus = minus + 1;
                        System.out.println("The vehicle with plate: " + v.getPlate()
                                + " has not passed the ITV, legal actions will be taken.");
                        printitv(v.getPlate()+"; ITV not passed;"+minus);
                    }
                    driver = v.getDriver();
                    break;
                }
            }
            if (driver == null) {
                System.out.println("No driver for the associated vehicle. Legal actions will be taken by the DGT");
            } else {
                suspended = driver.getLicense().removePoints(minus);
                points = driver.getLicense().getPoints();
                System.out.println("Driver " + driver.getName() + " loses " + minus + " points");
                points = driver.getLicense().getPoints();
                if (suspended == true) {
                    System.out.println("License suspended for driver " + driver.getName());
                } else if (points == 0) {
                    System.out.println("Driver " + driver.getName() + " remains with 0 points");
                }
            }
            System.out.println("====================================\n");
        }
        return;
    }

    /**
     * This function prints the cars that have been fined and have not passed the required ITV in a file "ITV_expired.txt"
     * @param text the text that will be written in the file
     */
    public static void printitv(String text) {
        try {
            File f = new File("./txt/ITV_expired.txt");
            f.createNewFile();

            FileWriter w = new FileWriter("./txt/ITV_expired.txt",true);
            w.write(text+"\n");
            w.close();

            
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

}