package components;
import vehicles.*;
/**
 * Creates components for the cars
 * 
 * @author Daniel Varela & Guillermo Martín-Coello
 *
 */
public interface IComponent {
	public boolean isDamaged();
	/**
	 * Sets if the component has damage
	 * 
	 * @param damage true if there is damage
	 */
	public void setDamaged(boolean damage);
	/**
	 * Gets the name of the component
	 * @return  component's name
	 */
	public String getName();
	/**
	 * Gets cost of the component reparation
	 * @return cost of the reparation
	 */
	public int costRepair();
	/**
	 * gets the vehicle interface
	 * @return vehicle interface
	 */
	public IVehicle getVehicle();
	/**
	* Gets weather the component is a critical one or not
	* @return true if it's critical false if it's not
	*/
	public boolean isCritical();
	/**
	 * Shows current state of repair
	 * @return current state of reparation
	 */
    public int currentRepair();
	/**
	 * Repairs the component
	 */
	public void repair();
}
