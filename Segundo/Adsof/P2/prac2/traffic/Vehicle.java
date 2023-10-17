
package prac2.traffic;

/**
 * This is a class for the vehicles common attributes
 * @author Guillermo Martin-Coello and Daniel Varela
 */
public abstract class Vehicle {
	private String model;
	private int purchaseYear;
	private String plate;
	
	/**
	 * This function serves as a constructor of the class Vehicle
	 * 
	 * @param mod this parameter stores the model of the vehicle
	 * @param a this parameter stores the purchase year of the vehicle
	 * @param plate this parameter stores the plate number of the vehicle
	 */
	public Vehicle(String mod, int a, String plate) {		
		this.model = mod;
		this.purchaseYear = a;
		this.plate = plate;
	}

	/**
	 * Function to print Vehicle information
	 * @return It returns the information you need to print about the vehicle
	 */
	@Override
	public String toString() {
		return "model "+this.model+", number plate: " + this.plate + ", purchase date "+this.purchaseYear+", with "+
				this.numWheels()+" wheels, index:"+this.getPollutionIndex();
	}
	
	/**
	 * this is a function that returns the number of wheels of the vehicle
	 * @return it returns nothing in this class because it will be overwritten in the other classes 
	 */
	public abstract int numWheels();
	
	/**
	 * this is a function to obtain the pollution index of the vehicle
	 * @return PollutionIndex.getPollutionIndex(this.purchaseYear) it returns te value the general procedure for obtaining the pollution returns
	 */
	public PollutionIndex getPollutionIndex() {
		return PollutionIndex.getPollutionIndex(this.purchaseYear);
	}

}