package prac2.traffic;


/**
 * This is a class for the car type of vehicle
 * @author Juan De Lara
 */
public class Car extends Vehicle {
	private boolean diesel;
	
	/**
	 * This function serves as a constructor of the class Car
	 * 
	 * @param mod A string with the model name
	 * @param a An integer with the purchase date
	 * @param plate A string with the plate number
	 * @param diesel A bool that contains whether the car is diesel or not
	 */
	public Car(String mod, int a, String plate, boolean diesel) {
		super(mod, a, plate);
		this.diesel = diesel;
	}

	
	/**
	 * Function that returns the number of wheels in a car
	 * @return 4 This function will always return 4 wheels if it's called from the Car class
	 */
	@Override public int numWheels() { return 4; }

	
	/**
	 * Function to print Car information
	 * @return It returns the information you need to print when the vehicle is of type Car
	 */
	@Override public String toString() {
		return "Car "+(this.diesel ? "diesel" : "gasoline") + ", "+ super.toString();
	}
	
	
	/**
	 * Function that checks for the pollution index of a Car
	 * @return It returns C as the pollution index if the car is diesel and if not it calls to the original getPollutionIndex function
	 */
	@Override
	public PollutionIndex getPollutionIndex() {
		if (this.diesel) return PollutionIndex.C;
		return super.getPollutionIndex();
	}
	
	
	/**
	 * This function returns the boolean diesel variable created in this class
	 * 
	 * @return this.diesel
	 */
	public boolean getDiesel() { return this.diesel; }

	
	/**
	 * This function sets the value of the diesel attribute in this class
	 * 
	 * @param b true if diesel
	 */
	public void setDiesel(boolean b) { this.diesel = b; }
}
