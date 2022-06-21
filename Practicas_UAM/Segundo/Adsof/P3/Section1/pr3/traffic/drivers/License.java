package pr3.traffic.drivers;
import java.util.*;

/**
 * This is a class that contains the license information
 */
public class License {
    private int points = 12;
    private Person owner;
    private static int unique = 0;
    private int identifier;
    private List<PermitKind> permits = new ArrayList<>();

    
    /**
     * This function provides a constructor for when creating a license with only one permits
     * @param permit1
     */
    public License (PermitKind permit1){
        this.permits.add(permit1);
        this.identifier = License.unique;
        License.unique = License.unique + 1;
    }

    /**
     * This function provides a constructor for when creating a license with two permits
     * @param permit1
     * @param permit2
     */
    public License (PermitKind permit1, PermitKind permit2){
        this.permits.add(permit1);
        this.permits.add(permit2);    

        this.identifier = License.unique;
        License.unique = License.unique + 1;
    }

    /**
     * This function provides a constructor for when creating a license with three permits
     * @param permit1
     * @param permit2
     * @param permit3
     */
    public License (PermitKind permit1, PermitKind permit2, PermitKind permit3){
        this.permits.add(permit1);
        this.permits.add(permit2);
        this.permits.add(permit3);

        this.identifier = License.unique;
        License.unique = License.unique + 1;
    }

    /**
     * Adds a new permit to the license
     * @param permit the permit we want to add
     * @return true if the permit can be aquired false otherwise
     */
    public boolean addPermit(PermitKind permit){
        if(owner.getAge()<permit.getMinAge()){
            return false;
        }
        this.permits.add(permit);
        return true;
    }

    /**
     * This function removes points from a license
     * @param penalty the amount of points that will be removed
     * @return true if the permit is now cancelled false otherwise
     */
    public boolean removePoints(int penalty){
        if(this.points==0){
            return true;
        }
        if((this.points-penalty)<=0){
            this.points=0;
        }
        else{
            this.points=this.points-penalty;
        }
        return false;
    }
    
    /**
     * Sets the owner of a license
     * @param owner the person that owns the license
     */
    public void addOwner(Person owner){
        this.owner=owner;
    }

    /**
     * This function checks if all the permits that a person has are valid for his age (this is to avoid errors if an age is reentered)
     * @param age the age of the person who we want to check its permits
     * @return true if all his permits are valid false if not
     */
    public boolean checkLegalAge(int age){
        for(PermitKind p : this.permits){  
            if(age<p.getMinAge()){
                return false;
            }
		}
        return true;
    }

	/**
	 * Function to print Person information
	 * 
	 * @return It returns the information you need to print when the User is of type
	 *         Person
	 */
	@Override
	public String toString() {
		return "License [id="+identifier+", permits="+permits+", points="+points+"]";
	}

    /**
     * gives the points of the license
     * @return points of the license
    */
    public int getPoints(){
        return this.points;
    }
    /**
     * gives the points of the license
     * @return points of the license
    */
    public List<PermitKind> getPermits(){
        return this.permits;
    }
    
}