package powerups;

import vehicles.*;
import components.*;

/**
 * Creates Shield power-up
 * 
 * @author Daniel Varela & Guillermo Martín-Coello
 *
 */
public class Shield implements IPowerUp {
    private String name;

	/**
	* Constructor for Shield power-up
	*/
	public Shield()	{
		this.name = "ShieldPowerUp";
	}
    
	/**
	* Applies the power up Shield to the specified vehicle
	* @param IVehicle v the vehicle you want to apply the power-up to 
	*/
	@Override
	public void applyPowerUp(IVehicle v){
		try {
            v.addComponent(new Component("Shield", 1, false, v));
		    System.out.println("Vehicle: "+v.getName()+" has now a "+this.namePowerUp()+" of: "+ (Double.valueOf(100/v.getComponents().size()))+"%");
		}	catch(InvalidComponentException e){
			System.out.println(e);
		}
	}
	
	/**
	* Gives the name of the power-up
	* @return string with the name of the power-up
	*/
	@Override
	public String namePowerUp()	{
		return this.name;
	}
}