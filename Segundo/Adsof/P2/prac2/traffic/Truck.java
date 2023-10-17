package prac2.traffic;

/**
 * This is a class for the truck type of vehicle
 * @author Guillermo Martin-Coello and Daniel Varela
 */

public class Truck extends Vehicle {
	private int axles;

	/**
	 * This function serves as a constructor of the class Truck
	 * 
	 * @param mod A string with the model name
	 * @param a An integer with the purchase date
	 * @param plate A string with the plate number
	 * @param axles An integer that contains the number of axles of the truck
	 */
	public Truck(String mod, int a, String plate, int axles) {
		super(mod, a, plate);
		this.axles = axles;
	}

	
	/**
	 * Function that returns the number of wheels in a truck
	 * @return axles*2 This function will always the double of the axles if it's called from the Truck class
	 */
	@Override public int numWheels() { return axles*2; }

	
	/**
	 * Function to print Truck information
	 * @return It returns the information you need to print when the vehicle is of type Truck
	 */
	@Override public String toString() {
		return "Truck with "+(this.axles) + " axles, "+ super.toString();
	}
	
	
	/**
	 * Function that checks for the pollution index of a Truck
	 * @return It returns C as the pollution index if the truck has more than 2 axles and if not it calls to the original getPollutionIndex function
	 */
	@Override
	public PollutionIndex getPollutionIndex() {
		if (this.axles>2) return PollutionIndex.C;
		return super.getPollutionIndex();
	}
	

	
	/**
	 * This function returns the integer containing the number of axles of a truck
	 * 
	 * @return this.axles
	 */
	public int getAxles() { return this.axles; }

	
	/**
	 * This function sets the value of the axles attribute in this class
	 * 
	 * @param a number of axis
	 */
	public void setAxles(int a) { this.axles = a; }
}
