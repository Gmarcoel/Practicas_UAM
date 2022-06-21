package vehicles;

import java.util.List;

import components.IComponent;
import components.InvalidComponentException;

/**
 * Interface with all the functions that the vehicle must have
 * 
 * @author Daniel Varela and Guillermo Martín-Coello
 *
 */
public interface IVehicle {
	
    /**
    * Gets the actual position of the vehicle
    * @return double with the position
    */
    public double getActualPosition();
    /**
    * Sets the actual position of the vehicle
    * @param newPosition double with the position you want to move the vehicle to
    */
    public void setActualPosition(double newPosition);
    /**
    * Gets whether the vehicle can move or not
    * @return boolean true if he can move and false otherwise
    */
    public boolean canMove();
    /**
    * Sets the value of can move to the value of the parameter
    * @param newMovement with the new value of can move
    */
    public void setCanMove(boolean newMovement);
    /**
    * Gets the max speed of the vehicle
    * @return double with the max speed of the vehicle
    */
    public double getMaxSpeed();
    /**
    * Gets the name of the vehicle
    * @return String with the name of the vehicle
    */
    public String getName();
    /**
	* updates the position of the vehicle and repairs if a component is damaged
	*/
    public void updatePosition();
        /**
    * Adds a new component to the list of components that the vehicle has
    * @param c IComponent with the component that wants to be added
    * @throws InvalidComponentException exception if component does not work as expected
    */
    public void addComponent(IComponent c) throws InvalidComponentException;
        /**
    * gets the list of components of the vehicle
    * @return the list of IComponents that the vehicle has
    */
    public List<IComponent> getComponents();
}