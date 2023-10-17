package prac2.traffic;

/**
 * This is a class for the motorcycle type of vehicle
 * @author Guillermo Martin-Coello and Daniel Varela
 */

public class Motorcycle extends Vehicle {
	private boolean electric;
	
	
	/**
	 * This function serves as a constructor of the class Motorcycle
	 * 
	 * @param mod A string with the model name
	 * @param a An integer with the purchase date
	 * @param plate A string with the plate number
	 * @param electric A bool that contains whether the motorcycle is electric or not
	 */
	public Motorcycle(String mod, int a, String plate, boolean electric) {
		super(mod, a, plate);
		this.electric = electric;
	}

	/**
	 * Function that returns the number of wheels in a motorcycle
	 * @return 2 This function will always return 2 wheels if it's called from the Motorcycle class
	 */
	@Override public int numWheels() { return 2; }


	/**
	 * Function to print Motorcycle information
	 * @return It returns the information you need to print when the vehicle is of type Motorcycle
	 */
	@Override public String toString() {
		return "Motorcycle" + (this.electric ? " electric" : "") + ", "+ super.toString();
	}
	
	/**
	 * Function that checks for the pollution index of a Motorcycle
	 * @return It returns A as the pollution index if the motorcycle is electric and if not it calls to the original getPollutionIndex function
	 */
	@Override
	public PollutionIndex getPollutionIndex() {
		if (this.electric) return PollutionIndex.A;
		return super.getPollutionIndex();
	}

	/**
	 * This function returns the boolean electric variable created in this class
	 * 
	 * @return this.electric
	 */
	public boolean getElectric() { return this.electric; }

	/**
	 * This function sets the value of the electric attribute in this class
	 * 
	 * @param b true if its electric
	 */
	public void setElectric(boolean b) { this.electric = b; }
}
