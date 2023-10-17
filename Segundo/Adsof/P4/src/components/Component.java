package components;

import vehicles.*;

/**
 * Creates components for the cars
 * 
 * @author Daniel Varela & Guillermo Martín-Coello
 *
 */
public class Component implements IComponent {
	private boolean damaged;
	private String name;
	private int costRepair;
	private int currentRepair;
	private IVehicle vehicle;
	private boolean critical;

	/**
	 * Class constructor
	 * 
	 * @param name       Name of the component
	 * @param costRepair cost int turns of the component reparation
	 * @param critical   true if component is critical
	 * @param vehicle    owner of the component
	 */
	public Component(String name, int costRepair, boolean critical, IVehicle vehicle) {
		this.name = name;
		this.costRepair = costRepair;
		this.critical = critical;
		this.vehicle = vehicle;
		this.damaged = false;
	}

	/**
	 * Checks if the component is damaged
	 * @return true if damaged
	 */
	public boolean isDamaged() {
		return this.damaged;
	}

	/**
	 * Sets if the component has damage
	 * 
	 * @param damage true if there is damage
	 */
	public void setDamaged(boolean damage) {
		this.damaged = damage;
		if (damage == true) {
			this.currentRepair = this.costRepair;
		}
	}

	/**
	 * Gets the name of the component
	 * @return  component's name
	 */
	public String getName() {
		return this.name;
	}
	/**
	 * Gets cost of the component reparation
	 * @return cost of the reparation
	 */
	public int costRepair() {
		return this.costRepair;
	}
	/**
	 * gets the vehicle interface
	 * @return vehicle interface
	 */
	public IVehicle getVehicle() {
		return this.vehicle;
	}

	/**
	* Gets weather the component is a critical one or not
	* @return true if it's critical false if it's not
	*/
	public boolean isCritical() {
		return this.critical;
	}
	/**
	 * Repairs the component
	 */
	public void repair() {
		if (this.isDamaged() == true) {
			this.currentRepair--;
			if (this.currentRepair <= 0) {
				this.setDamaged(false);
			}
		}
	}
	/**
	 * Shows current state of repair
	 * @return current state of reparation
	 */
	public int currentRepair() {
		return this.currentRepair;
	}
	/**
	 * prints attributes through output
	 * @return string of attributes
	 */
	@Override
	public String toString() {
		// String color=(this.isDamaged()) ? "\\u001B[41m" : "\\u001B[40m";
		return (" ->" + this.getName() + ". Is damaged: " + this.isDamaged() + ". Is critical: " + this.isCritical()
				+ "\n");
	}
}
