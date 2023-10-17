package powerups;

import races.*;
import vehicles.*;


/**
 * Creates AttackAll power-up
 * 
 * @author Daniel Varela & Guillermo Martín-Coello
 *
 */
public class AttackAll implements IPowerUp{
    private String name;
    private Race race;
	/**
	* Constructor for AttackAll power-up
	* @param race with the race you want to apply the power-up to
	*/
	public AttackAll(Race race)	{
		this.name = "AttackAllPowerUp";
		this.race = race;
	}
	
	/**
	* Applies the power up AttackAll to the specified vehicle
	* @param IVehicle v the vehicle you want to apply the power-up to 
	*/
	@Override
	public void applyPowerUp(IVehicle v) {
		System.out.println("Vehicle: "+v.getName()+" applying power-up: "+this.namePowerUp());
		
		for (IVehicle iv : this.race.getVehicles()) {
			if(!(iv.equals(v)))	{
				race.attack(v, iv);
			}
			
		
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