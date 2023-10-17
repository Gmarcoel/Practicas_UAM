package pr3.traffic.vehicles;

import pr3.traffic.drivers.*;
import java.util.*;

/**
 * This is a class for the vehicles common attributes
 * 
 * @author Guillermo Martin-Coello and Daniel Varela
 */
public abstract class Vehicle {
	private String model;
	protected int purchaseYear;
	private String plate;
	private User owner;
	private Person driver = null;
	protected ArrayList<ITV> itvs = new ArrayList<>();

	/**
	 * This function serves as a constructor of the class Vehicle
	 * 
	 * @param mod   this parameter stores the model of the vehicle
	 * @param a     this parameter stores the purchase year of the vehicle
	 * @param plate this parameter stores the plate number of the vehicle
	 */
	public Vehicle(String mod, int a, String plate) {
		this.model = mod;
		this.purchaseYear = a;
		this.plate = plate;
	}

	/**
	 * This function serves as a constructor of the class Vehicle if you indicate
	 * also the owner in the constructor
	 * 
	 * @param mod   this parameter stores the model of the vehicle
	 * @param a     this parameter stores the purchase year of the vehicle
	 * @param plate this parameter stores the plate number of the vehicle
	 * @param user  this parameter stores the owner of the vehicle
	 */
	public Vehicle(String mod, int a, String plate, User user) {
		this.model = mod;
		this.purchaseYear = a;
		this.plate = plate;
		setOwner(user);
	}

	/**
	 * This function sets the owner of the vehicle which can be a person or a
	 * company
	 * 
	 * @param owner this parameter is the person/company that owns the car
	 */
	public void setOwner(User owner) {
		this.owner = owner;
		owner.addVehicle(this);
		if (this.driver == null) {
			if (owner instanceof Person) {
				setDriver((Person) owner);
			} else {
				setDriver(((Company) owner).getResponsible());
			}
		}
	}

	/**
	 * This function sets a driver of type person to the vehicle if that person can
	 * drive
	 * 
	 * @param driver this parameter is the peson hat is driving the car
	 * @return it returns true if the driver has been set to the vehicle and false
	 *         if the peson can not drive the vehicle
	 */
	public boolean setDriver(Person driver) {
		if (canDriveVehicle(driver)) {
			this.driver = driver;
			return true;
		}
		return false;
	}

	/**
	 * This function checks if the person we introduce as a parameter can drive the
	 * current vehicle (works for cars)
	 * 
	 * @param driver the person we want to check if he can drive the vehicle
	 * @return true if it can false otherwise
	 */
	public boolean canDriveVehicle(Person driver) {
		if(driver.getLicense()==null) return false;
			for (PermitKind p : driver.getLicense().getPermits()) {
				if (p == PermitKind.B) {
					return true;
				}
			}
		
		return false;
	}

	/**
	 * Function to print Vehicle information
	 * 
	 * @return It returns the information you need to print about the vehicle
	 */
	@Override
	public String toString() {
		if (driver == null) {
			return "model " + this.model + ", number plate: " + this.plate + ", purchase date " + this.purchaseYear
					+ ", with " + this.numWheels() + " wheels, index:" + this.getPollutionIndex() + ", owner: "
					+ this.owner.getName() + ", driver: not registered";

		}
		return "model " + this.model + ", number plate: " + this.plate + ", purchase date " + this.purchaseYear
				+ ", with " + this.numWheels() + " wheels, index:" + this.getPollutionIndex() + ", owner: "
				+ this.owner.getName() + ", driver: " + this.driver.getName();
	}

	/**
	 * this is a function that returns the number of wheels of the vehicle
	 * 
	 * @return it returns nothing in this class because it will be overwritten in
	 *         the other classes
	 */
	public abstract int numWheels();

	/**
	 * this is a function to obtain the pollution index of the vehicle
	 * 
	 * @return PollutionIndex.getPollutionIndex(this.purchaseYear) it returns te
	 *         value the general procedure for obtaining the pollution returns
	 */
	public PollutionIndex getPollutionIndex() {
		return PollutionIndex.getPollutionIndex(this.purchaseYear);
	}

	/**
	 * gives the current plate of the vehicle
	 * 
	 * @return vehicle's plate
	 */
	public String getPlate() {
		return this.plate;
	}

	/**
	 * This function gives the current driver of the vehicle
	 * 
	 * @return the person who is driving the vehicle
	 */
	public Person getDriver() {
		return this.driver;
	}

	/**
	 * This function adds a new itv to the vehicle's itvs
	 * 
	 * @param itv the itv that will be added
	 */
	public void addITV(ITV itv) {
		this.itvs.add(itv);
		itv.garage.addVehicle(this);
	}

	/**
	 * This function checks if the last itv added to the vehicle is still valid
	 * (works for cars and motorcycles)
	 * 
	 * @return true if it's valid false if it isn't
	 */
	public boolean checkITV() {
		ITV lastITV;
		int age;
		int lastitvyear;
		if (itvs.size() >= 1) {
			lastITV = this.itvs.get(itvs.size() - 1);
			age = java.time.LocalDate.now().getYear() - this.purchaseYear;
			lastitvyear = java.time.LocalDate.now().getYear() - lastITV.getYear();
			if (age <= 4) {
				return true;
			} else if (age <= 10) {
				if (lastitvyear > 2) {
					return false;
				} else {
					return true;
				}
			} else {
				if (lastitvyear > 1) {
					return false;
				} else {
					return true;
				}
			}
		}
		return false;
	}


}


