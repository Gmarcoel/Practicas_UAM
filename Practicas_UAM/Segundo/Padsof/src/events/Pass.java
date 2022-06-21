package events;

import javax.persistence.*;

import java.io.*;
import java.util.*;
import zones.*;

/**
 * This is a class that allow us to define a pass
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier LÃ³pez de la Nieta LujÃ¡n
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public abstract class Pass implements Serializable {
	private double price;
	private Zone zone;
	private ArrayList<Event> alreadyAttended;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param zone related the pass
	 */
	public Pass(Zone zone) {
		if (zone == null) {
			System.out.println("Error:invalid zone");
		}
		this.zone = zone;
		this.alreadyAttended = new ArrayList<Event>();

	}

	/**
	 * Method to get the list of the events already attended
	 * 
	 * @return an arraylist with the events
	 */
	public ArrayList<Event> getAlreadyAttendedList() {
		return this.alreadyAttended;
	}

	/**
	 * Method to get the zone realted to the pass
	 * 
	 * @return the zone of the pass
	 */
	public Zone getZone() {
		return this.zone;
	}
	
	/**
	 * Method to set the zone related to the pass
	 * 
	 * 
	 * @param z the zone of the pass
	 */
	public void setZone(Zone z) {
		this.zone=zone;
	}

	/**
	 * Method to add an event to the alrady attended list
	 * 
	 * @param event to be added
	 */
	public void addAlreadyAttended(Event event) {
		if (event == null) {
			System.out.println("Error:invalid event");
			return;
		}
		this.alreadyAttended.add(event);
	}

	/**
	 * Method to check if a user has already attended to an event
	 * 
	 * @param event to be checked
	 * @return boolean if has attended
	 */
	public boolean getIfHasAlreadyAttended(Event event) {
		if (event == null) {
			System.out.println("Error:invalid event");
			return false;
		}
		for (Event e : this.alreadyAttended) {
			if (e == event) {
				return true;
			}
		}
		return false;
	}

	/**
	 * Method to get the name of a pass(is an abstract class, so we override this
	 * method)
	 * 
	 * @return the name of the pass
	 */
	public String getName() {
		return ("");
	}

	/**
	 * Method to get the price of a pass
	 * 
	 * @return the name of the pass
	 */
	public double getPrice() {
		return this.price;
	}

	/**
	 * Method to set the price of a pass
	 * 
	 * @param p to be established
	 */
	public void setPrice(double p) {
		this.price = p;
	}

	/**
	 * Method to make a copy of the pass
	 * 
	 * @return pass copied
	 */
	public abstract Pass copyPass();

}
