package powerups;

import java.text.DecimalFormat;

import races.*;
import vehicles.*;


/**
 * Creates Swap power-up
 * 
 * @author Daniel Varela & Guillermo Martín-Coello
 *
 */
public class Swap implements IPowerUp{
    private String name;
    private Race race;
	
	/**
	* Constructor for Swap power-up
	* @param race with the race you want to apply the power-up to
	*/
	public Swap(Race race)	{
		this.name = "SwapPowerUp";
		this.race = race;
	}
	
	/**
	* Applies the power up Swap to the specified vehicle
	* @param IVehicle v the vehicle you want to apply the power-up to 
	*/
	@Override
	public void applyPowerUp(IVehicle v) {
		DecimalFormat numberFormat = new DecimalFormat("#.00");
		System.out.println("Vehicle: "+v.getName()+" applying power-up: "+this.namePowerUp());
        double posv=v.getActualPosition();
        IVehicle v2 = this.race.getCloserVehicle(v);
        if(v2==null){
		System.out.println("Vehicle: "+v.getName()+" failed to apply power-up: "+this.namePowerUp());}
        else{
        double posv2=v2.getActualPosition();
        v.setActualPosition(posv2);
        v2.setActualPosition(posv);
        
        
		System.out.println(v.getName()+" was on: "+numberFormat.format(v2.getActualPosition())+" with swap is now on "+numberFormat.format(v.getActualPosition()));
		System.out.println(v2.getName()+" was on: "+numberFormat.format(v.getActualPosition())+" with swap is now on "+numberFormat.format(v2.getActualPosition()));
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
