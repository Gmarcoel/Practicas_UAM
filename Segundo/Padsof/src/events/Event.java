package events;

import javax.persistence.*;
import java.io.*;
import performances.*;
import java.util.*;
import zones.*;
import java.time.*;

/**
 * This is an abstract class that allow us to define an event
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier LÃ³pez de la Nieta LujÃ¡n
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public abstract class Event implements Serializable {
	protected String title;
	private String author;
	private String director;
	private String description;
	private ArrayList<Performance> performances;
	private ArrayList<Price> prices;
	private int duration;
	
	/**
	 * Constructor, with the attributes
	 * 
	 * @param title       string with the title of the event
	 * @param author      String with the author of the event
	 * @param director    string that contains the director of the event
	 * @param description string with a short description of the event
	 */
	public Event(String title, String author, String director, String description) {

		if (title.isBlank() || author.isBlank() || director.isBlank() || description.isBlank()) {
			System.out.println("Error:invalid string");
			return;
		}
		this.title = title;
		this.author = author;
		this.director = director;
		this.description = description;
		performances = new ArrayList<Performance>();
		prices = new ArrayList<Price>();
	}

	/**
	 * Constructor, with the attributes
	 * 
	 * @param title string with the title of the event (used to create cycles)
	 */
	public Event(String title) {
		if (title.isBlank()) {
			System.out.println("Error:invalid string");
			return;
		}
		this.title = title;
	}

	/**
	 * Method to get a performance given a date
	 * 
	 * @param date of the requested performance
	 * @return the performance with the given date
	 */
	public Performance getPerformance(LocalDateTime date) {
		if (date == null) {
			System.out.println("Error:invalid date");
			return null;
		}
		for (Performance p : this.performances) {
			if (p.getDate().equals(date)) {
				return p;
			}
		}
		return null;
	}
	/**
	 * Method to add a performance without creating one
	 *
	 * @param performance to add
	 */
	public void addPerformance(Performance performance) {
		if(performance==null) {
			System.out.println("Error: Invalid performance argument\n");
			return;
		}
		this.performances.add(performance);
	}

	/**
	 * Method to delete a performance from the list of the event
	 * 
	 * @param performance to be eliminated
	 */
	public void cancelPerformance(Performance performance) {
		if (performance == null) {
			System.out.println("Error:invalid performance");
			return;
		}
		this.performances.remove(performance);
	}

	/**
	 * Method to get the list of performances that an event has
	 * 
	 * @return an arraylist with the performances of the event
	 */
	public ArrayList<Performance> getPerformances() {
		return this.performances;
	}

	/**
	 * Method to add a price to the event
	 * 
	 * @param p to be added
	 */
	public void addPrice(Price p) {
		if (p == null) {
			System.out.println("Error:invalid price");
			return;
		}
		this.prices.add(p);
	}

	/**
	 * Method to set the price of a selected zone
	 * 
	 * @param zone in which we want to establish the price
	 * @param price to be set in the correspondant zone
	 */
	public void setPrice(Zone zone, double price) {
		if (zone == null) {
			System.out.println("Error:the zone doens't exist\n");
			return;
		}
		if (price < 0) {
			System.out.println("Error:invalid price\n");
			return;
		}
		for (Price p : this.prices) {
			if (p.getZone().getName().equals(zone.getName())) {
				p.setPrice(price);
				return;
			}
		}
		this.prices.add(new Price(zone, price));
	}

	/**
	 * Method to get a price of an event given a zone
	 * 
	 * @param zone that we want to get the price
	 * @return price of the zone
	 */
	public double getPrice(Zone zone) {
		if (zone == null) {
			System.out.println("Error:invalid zone");
			return -1;
		}
		for (Price p : this.prices) {
			if (p.getZone().getName().equals(zone.getName())) {
				return p.getPrice();
			}
		}
		return 0;
	}

	/**
	 * Method to get a list with all the prices of the event
	 * 
	 * @return arraylist with all the prices
	 */
	public ArrayList<Price> getPrices() {
		return this.prices;
	}

	/**
	 * Method to get the title of the event
	 * 
	 * @return string with the title
	 */
	public String getTitle() {
		return this.title;
	}

	/**
	 * Method to get a the author of the event
	 * 
	 * @return string with the author
	 */
	public String getAuthor() {
		return this.author;
	}

	/**
	 * Method to get the director of an event
	 * 
	 * @return string with the director
	 */
	public String getDirector() {
		return this.director;
	}

	/**
	 * Method to get the description of an event
	 * 
	 * @return string with the description of the event
	 */
	public String getDescription() {
		return this.description;
	}

	/**
	 * Method to set the title of an event
	 * 
	 * @param title to be established
	 */
	public void setTitle(String title) {
		if (title.isBlank()) {
			System.out.println("Error:invalid string");
			return;
		}
		this.title = title;
	}

	/**
	 * Method to set the author of an event
	 * 
	 * @param author to be established
	 */
	public void setAuthor(String author) {
		if (author.isBlank()) {
			System.out.println("Error:invalid string");
			return;
		}
		this.author = author;
	}

	/**
	 * Method to set the director of an event
	 * 
	 * @param director to be established
	 */
	public void setDirector(String director) {
		if (director.isBlank()) {
			System.out.println("Error:invalid string");
			return;
		}
		this.director = director;
	}

	/**
	 * Method to set the description of an event
	 * 
	 * @param description to be established
	 */
	public void setDescription(String description) {
		if (description.isBlank()) {
			System.out.println("Error:invalid string");
			return;
		}
		this.description = description;
	}

	/**
	 * Method to create a performance of an event
	 * 
	 * @param date  of the performance
	 * @param zones of the theater to make a copy in each performance
	 * 
	 * @return bool with the outcome of the creation
	 */
	public boolean createPerformance(LocalDateTime date, ArrayList<Zone> zones) {
		if (date == null || zones == null) {
			System.out.println("Error:invalid date or list of events");
			return false;
		}
		if (date.isBefore(LocalDateTime.now())) {
			System.out.println("Error: Performance constructor recieves an invalid date\n");
			return false;
		}
		for (Zone z : zones) {
			this.prices.add(new Price(z));
		}
		this.performances.add(new Performance(date, zones, this));
		return true;
	}

	/**
	 * Method to check if a performance of an event exist given a localdate
	 * 
	 * @param date of the performance
	 * @return if the zone exists or not
	 */
	public boolean checkIfPerformanceExist(LocalDateTime date) {
		if (date == null) {
			System.out.println("Error:invalid date");
			return true;
		}
		for (Performance i : this.performances) {
			if (i.getDate().equals(date)) {
				return true;
			}
		}
		return false;
	}

	
	/**
	 * Setter for the duration of the event
	 * 
	 * @param d with the new duration
	 */
	public void setDuration(int d){
		this.duration=d;
	}

	/**
	 * Getter for the duration of the event
	 * 
	 * @return the duration of the event
	 */
	public int getDuration(){
		return this.duration;
	}
}
