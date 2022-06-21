package vehicles;

import java.text.DecimalFormat;
import java.util.*;
import components.*;

/**
 * Creates a vehicle 
 * 
 * @author Daniel Varela and Guillermo Martín-Coello
 *
 */
public class Vehicle implements IVehicle{

    protected static int identifier = 1;
    protected String name;
    protected double maxSpeed;
    protected double position;
    private boolean canMove;
    protected List<IComponent> components;

	/**
	* Constructor for the class vehicle
	* @param maxSpeed a double with the maximum speed of the vehicle
	* @param type a string with the type of vehicle it is
	*/
    public Vehicle(double maxSpeed, String type) {
        this.position=0;
        this.name=type+"("+identifier+")";
        this.maxSpeed=maxSpeed;
        identifier=identifier+1;
        components = new ArrayList<IComponent>();
    }


    /**
    * Gets the max speed of the vehicle
    * @return double with the max speed of the vehicle
    */
    public double getMaxSpeed(){
        return this.maxSpeed;
    }


    /**
    * Gets the name of the vehicle
    * @return String with the name of the vehicle
    */
    public String getName(){
        return this.name;
    }


    /**
    * Gets whether the vehicle can move or not
    * @return boolean true if he can move and false otherwise
    */
    public boolean canMove(){
        return this.canMove;
    }


    /**
    * Sets the value of can move to the value of the parameter
    * @param newMovement with the new value of can move
    */
    public void setCanMove(boolean newMovement){
        this.canMove=newMovement;
    }
    
    
    /**
    * Gets the actual position of the vehicle
    * @return double with the position
    */
    public double getActualPosition(){
        return this.position;
    }
    
    
    /**
    * Sets the actual position of the vehicle
    * @param newPosition double with the position you want to move the vehicle to
    */
    public void setActualPosition(double newPosition){
        this.position=newPosition;
    }
    

    /**
	* updates the position of the vehicle and repairs if a component is damaged
	*/
    public void updatePosition() {
        for(IComponent ic : this.getComponents()){
            if (ic.isDamaged()&&ic.isCritical()){
                ic.repair();
                return;
            }
            else if (ic.isDamaged()){
                ic.repair();
            }
        }
    	this.position += this.maxSpeed;
    }

    /**
    * Adds a new component to the list of components that the vehicle has
    * @param c IComponent with the component that wants to be added
    */
    public void addComponent(IComponent c) throws InvalidComponentException{
        if(this.components.add(c)==false){
            throw new InvalidComponentException();
        }
    }


    /**
    * gets the list of components of the vehicle
    * @return the list of IComponents that the vehicle has
    */
    public List<IComponent> getComponents(){
        return this.components;
    }


    /**
    * Returns the information of the vehicle
    * @return String with the information of the vehicle
    */
    @Override
    public String toString() {
        String output="";
        DecimalFormat numberFormat = new DecimalFormat("#.00");
        output += this.getName()+". Speed "+ maxSpeed + ". Actual position: "+ numberFormat.format(this.getActualPosition()) +".\n";
        for(IComponent ic : this.getComponents()){
        	output+=ic;
        }
        return output;
    }
}
