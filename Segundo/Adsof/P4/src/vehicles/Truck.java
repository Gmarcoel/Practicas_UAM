package vehicles;

import java.util.*;


/**
 * Creates a vehicle of type truck
 * 
 * @author Daniel Varela & Guillermo Martín-Coello
 *
 */
public class Truck extends Vehicle {

	/**
	* Constructor for the class truck
	* @param maxSpeed a double with the maximum speed of the vehicle
	*/
	public Truck(double maxSpeed) {
		super(maxSpeed, "Truck");
	}


    /**
	* updates the position of the truck
	*/
	@Override
	public void updatePosition() {
		SplittableRandom random = new SplittableRandom();
		if (random.nextInt(10) == 0) {

			this.position += this.maxSpeed * .8;
		} else {
			super.updatePosition();
		}
	}

}
