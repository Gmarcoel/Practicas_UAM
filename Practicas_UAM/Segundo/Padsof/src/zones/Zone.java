package zones;

import java.io.*;

/**
 * This is an abstract class that allow us to define a zone
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public abstract class Zone implements Serializable {

	private String name;
	protected int occupancy;
	private FragmentedZone dad = null;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param name of the zone to be created
	 */
	public Zone(String name) {
		if (name.isBlank()) {
			System.out.println("Error: Empty name \n");
			return;
		}
		this.name = name;
		this.occupancy = 100;
	}

	/**
	 * Method to get the name of a zone
	 * 
	 * @return string with the name of the zone
	 */
	public String getName() {
		return this.name;
	}

	/**
	 * Method to set the dad
	 * 
	 * @param dad parent of the zone
	 */
	public void setDad(FragmentedZone dad) {
		this.dad = dad;
	}

	/**
	 * Method to get the function's parent
	 * 
	 * @return fragmented zone corresponding to the parent
	 */
	public FragmentedZone getDad() {
		return this.dad;
	}

	/**
	 * Method to set the name of a zone
	 * 
	 * @param name to be established in the zone
	 */
	public void setName(String name) {
		if (name.isBlank()) {
			System.out.println("Error: Empty name \n");
			return;
		}
		this.name = name;
		return;
	}

	/**
	 * Method to get the attendees of a zone(is abstract, we override it)
	 * 
	 * @return int with the number of attendees
	 */
	public abstract int getAttendees();

	/**
	 * Method to occupy a unique place in the zone(we override it)
	 */
	public void occupy() {
		return;
	}
/**
 * gets the occupancy of the zone
 *	
 *@return int with the occupancy 
 */
	public int getOccupancy() {
		return this.occupancy;
	}

	/**
	 * Method to set the occupancy in a zone
	 * 
	 * @param o with the occupancy percentage to establish in the zone
	 */
	public void setOccupancy(int o) {
		if (o < 0 || o > 100) {
			System.out.println("Error: Number is not between expected range \n");
			return;
		}
		this.occupancy = o;
	}

	/**
	 * Method to get the number of people in a zone(we override it)
	 * 
	 * @return int with the number of people
	 */
	public abstract int getNPosPeople();

	/**
	 * Method to get the maximum number of people in a zone(we override it)
	 * 
	 * @return int with the maximum number of people
	 */
	public abstract int getNMaxPeople();

	/**
	 * Method to create a copy of the zone(is abstract, we override it)
	 * 
	 * @return zone clonated
	 */
	public abstract Zone cloneZone();

}
