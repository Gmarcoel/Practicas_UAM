package pr3.traffic.vehicles;

import pr3.traffic.drivers.*;

/**
 * This is a class for the truck type of vehicle
 * 
 * @author Guillermo Martin-Coello and Daniel Varela
 */

public class Truck extends Vehicle {
	private int axles;

	/**
	 * This function serves as a constructor of the class Truck
	 * 
	 * @param mod   A string with the model name
	 * @param a     An integer with the purchase date
	 * @param plate A string with the plate number
	 * @param axles An integer that contains the number of axles of the truck
	 */
	public Truck(String mod, int a, String plate, int axles) {
		super(mod, a, plate);
		this.axles = axles;
	}

	/**
	 * This function serves as a constructor of the class Truck if you also indicate
	 * the owner
	 * 
	 * @param mod   A string with the model name
	 * @param a     An integer with the purchase date
	 * @param plate A string with the plate number
	 * @param axles An integer that contains the number of axles of the truck
	 * @param owner A parameter of type User which indicates the owner of the truck
	 */
	public Truck(String mod, int a, String plate, int axles, User owner) {
		super(mod, a, plate, owner);
		this.axles = axles;
	}

	/**
	 * Function that returns the number of wheels in a truck
	 * 
	 * @return axles*2 This function will always the double of the axles if it's
	 *         called from the Truck class
	 */
	@Override
	public int numWheels() {
		return axles * 2;
	}

	/**
	 * Function to print Truck information
	 * 
	 * @return It returns the information you need to print when the vehicle is of
	 *         type Truck
	 */
	@Override
	public String toString() {
		return "Truck with " + (this.axles) + " axles, " + super.toString();
	}

	/**
	 * Function that checks for the pollution index of a Truck
	 * 
	 * @return It returns C as the pollution index if the truck has more than 2
	 *         axles and if not it calls to the original getPollutionIndex function
	 */
	@Override
	public PollutionIndex getPollutionIndex() {
		if (this.axles > 2)
			return PollutionIndex.C;
		return super.getPollutionIndex();
	}

	/**
	 * This function returns the integer containing the number of axles of a truck
	 * 
	 * @return this.axles
	 */
	public int getAxles() {
		return this.axles;
	}

	/**
	 * This function sets the value of the axles attribute in this class
	 * 
	 * @param a number of axles
	 */
	public void setAxles(int a) {
		this.axles = a;
	}

	/**
	 * This function checks if the person we introduce as a parameter can drive the
	 * current truck
	 * 
	 * @param driver the person we want to check if he can drive the vehicle
	 * @return true if it can false otherwise
	 */
	@Override
	public boolean canDriveVehicle(Person driver) {
		if(driver.getLicense()==null) return false;
			for (PermitKind p : driver.getLicense().getPermits()) {
				if (p == PermitKind.C1) {
					return true;
				}
			}
		return false;
	}

	/**
	 * This function checks if the last itv added to the truck is still valid
	 * 
	 * @return true if it's valid false if it isn't
	 */
	@Override
	public boolean checkITV() {
		ITV lastITV;
		int truckAge;
		int lastitvyear;
		int lastitvmonth;
		if (itvs.size() >= 1) {
			lastITV = this.itvs.get(itvs.size() - 1);
			truckAge = java.time.LocalDate.now().getYear() - this.purchaseYear;
			lastitvyear = java.time.LocalDate.now().getYear() - lastITV.getYear();
			lastitvmonth = java.time.LocalDate.now().getMonthValue() - lastITV.getMonth();
			if (truckAge <= 2) {
				return true;
			} else if (truckAge <= 6) {
				if (lastitvyear > 2) {
					return false;
				} else {
					return true;
				}
			} else if (truckAge <= 10) {
				if (lastitvyear > 2) {
					return false;
				} else {
					return true;
				}
			} else {
				if (lastitvyear == 0) {
					if (lastitvmonth < 6)
						return true;
				} else if (lastitvyear == 1) {
					if (lastitvmonth + 12 < 6) {
						return true;
					}
				}

				return false;
			}
		}
		return false;

	}
}
