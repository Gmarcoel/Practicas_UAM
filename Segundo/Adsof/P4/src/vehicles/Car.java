package vehicles;

import java.util.SplittableRandom;

/**
 * Creates a vehicle of type car
 * 
 * @author Daniel Varela & Guillermo Martín-Coello
 *
 */
public class Car extends Vehicle {

	/**
	* Constructor for the class car
	* @param maxSpeed a double with the maximum speed of the vehicle
	*/
    public Car (double maxSpeed){
        super(maxSpeed, "Car");
    }
    

    /**
	* updates the position of the car
	*/
    @Override
	public void updatePosition() {
		SplittableRandom random = new SplittableRandom();
		if (random.nextInt(10) == 0) {

			this.position += this.maxSpeed * .9;
		} else {
			super.updatePosition();
		}
	}
}
