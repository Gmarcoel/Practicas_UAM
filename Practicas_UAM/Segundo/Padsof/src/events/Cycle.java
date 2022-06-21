package events;

import javax.persistence.*;

import java.io.*;
import java.util.*;
import zones.*;

/**
 * This is a class that allow us to create a Â¡cycle
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier LÃ³pez de la Nieta LujÃ¡n
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class Cycle extends Event {
	private ArrayList<Event> events;
	// private CyclePass cyclePass;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param title string with the name of the cycle
	 */
	public Cycle(String title) {
		super(title);
		if (title.isBlank()) {
			System.out.println("Error:invalid string");
			return;
		}
		this.events = new ArrayList<>();
	}

	/**
	 * Method to add an event to a cycle
	 * 
	 * @param event to added
	 */
	public void addEvent(Event event) {
		if (event == null) {
			System.out.println("Error:invalid event");
			return;
		}
		this.events.add(event);
	}

	/**
	 * Method to get the events that a cycle contains
	 * 
	 * @return an arraylist with the events of the cycle
	 */
	public ArrayList<Event> getEvents() {
		return this.events;
	}

	/**
	 * Method that calculates the total price of the events contained in a cycle
	 * 
	 * @param zone with the zone 
	 * 
	 * @return a double with the total price
	 */
	public double calculateSumPrice(Zone zone) {

		double total = 0;

		if (zone == null) {
			System.out.println("Error:invalid zone");
			return -1;
		}

		for (Event e : this.getEvents()) {
			if (e instanceof Cycle) {
				total += ((Cycle) e).calculateSumPrice(zone);
			} else {
				total += e.getPrice(zone);
			}
		}
		return total;
	}

	/**
	 * Method that gets the name of the cycle
	 * 
	 * @return a string with the title
	 */
	public String getTitle() {
		return this.title;
	}	
	
	public void changeCycle(String name, ArrayList<Event> event) {
		this.events=event;
		this.title=name;
	}
	
}
