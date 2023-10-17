package powerups;
import vehicles.*;

/**
 * Interface with all the functions that the power ups must have
 * 
 * @author Daniel Varela & Guillermo Martín-Coello
 *
 */
public interface IPowerUp {
	/**
	* Applies the power up to the specified vehicle
	* @param IVehicle v the vehicle you want to apply the power-up to 
	*/
    public void applyPowerUp(IVehicle v);
    
	/**
	* Gives the name of the power-up
	* @return string with the name of the power-up
	*/
    public String namePowerUp();
}
