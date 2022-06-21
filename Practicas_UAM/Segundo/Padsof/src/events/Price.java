package events;

import java.io.*;

import javax.persistence.*;
import zones.*;

/**
 * This is a class that allow us to create a price relating a price with a zone
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class Price implements Serializable {
	private Zone zone;
	private double price;
	private Event event = null;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param zone  in wich we want to establish a price
	 * @param price to be established
	 */
	public Price(Zone zone, double price) {
		if (zone == null || price < 0) {
			System.out.println("Error:invalid zone or price");
			return;
		}
		this.zone = zone;
		this.price = price;
	}

	/**
	 * Constructor, with the attributes
	 * 
	 * @param zone in wich we want to establish a price
	 */
	public Price(Zone zone) {
		if (zone == null) {
			System.out.println("Error:invalid zone");
			return;
		}
		this.zone = zone;
		this.price = 0;
	}
	
	/**
	 * Method to set the event of a price
	 * 
	 * @param event to be set
	 */
	public void setEvent(Event event) {
		this.event = event;
	}
	
	/**
	 * Method to set the event of a price
	 * 
	 * @return event related to the price
	 */
	public Event getEvent() {
		return this.event;
	}

	/**
	 * Method to get the the price of the Price
	 * 
	 * @return double with the price
	 */
	public double getPrice() {
		return this.price;
	}

	/**
	 * Method to get the zone related to a Price
	 * 
	 * @return the zone of the Price
	 */
	public Zone getZone() {
		return this.zone;
	}

	/**
	 * Method to set the price of a Price
	 * 
	 * @param price to be established
	 */
	public void setPrice(double price) {
		if (price < 0) {
			System.out.println("Error:invalid price");
			return;
		}
		this.price = price;
	}
}
