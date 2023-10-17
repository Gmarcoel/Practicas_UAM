package vehicles;
import components.*;


/**
 * Creates a vehicle of type motorcycle
 * 
 * @author Daniel Varela and Guillermo Martín-Coello
 *
 */
public class Motorcycle extends Vehicle{

	/**
	* Constructor for the class motorcycle
	* @param maxSpeed a double with the maximum speed of the vehicle
	*/
    public Motorcycle (double maxSpeed){
        super(maxSpeed, "Motorcycle");
    }
    
    @Override
    public void addComponent(IComponent c) throws InvalidComponentException{
        if(c.getName()!="Engine" && c.getName()!="Wheels" && c.getName()!="Shield"){
            throw new InvalidComponentException();
        }
        if(this.components.add(c)==false){
            throw new InvalidComponentException();
        }
    }

}
