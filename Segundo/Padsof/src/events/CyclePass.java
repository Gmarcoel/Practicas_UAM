package events;

import javax.persistence.*;
import zones.*;
import java.util.ArrayList;

/**
 * This is a class that allow us to create a cycle pass
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier LÃƒÂ³pez de la Nieta LujÃƒÂ¡n
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class CyclePass extends Pass {
	private String name;
	private int discountPercentage;
	private Cycle cycle;
	private ArrayList<Event> canGoTo;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param name               of the cycle pass
	 * @param discountPercentage applied to the pass
	 * @param zone               related to the pass
	 * @param cycle              corresponding to the cycle pass
	 */
	public CyclePass(String name, int discountPercentage, Zone zone, Cycle cycle) {
		super(zone);
		if (name.isBlank() || zone == null || cycle == null) {
			System.out.println("Error:invalid name, zone or cycle");
			return;
		}
		if (discountPercentage < 0 || discountPercentage > 100) {
			System.out.println("Error:invalid percentage");
			return;
		}
		this.name = name;
		this.discountPercentage = discountPercentage;
		this.cycle = cycle;
		double p = calculateDiscountedPrice();
		super.setPrice(p);
		this.canGoTo = this.setCanGoToList(cycle.getEvents());
	}

	/**
	 * Method to set the name of the cycle pass
	 * 
	 * @param name to be established
	 */
	public void setName(String name) {
		if (name.isBlank()) {
			System.out.println("Error:invalid name");
			return;
		}
		this.name = name;
	}

	/**
	 * Method to set the discount of the cycle pass
	 * 
	 * @param discountPercentage to be established
	 */
	public void setDiscountPercentage(int discountPercentage) {
		if (discountPercentage < 0 || discountPercentage > 100) {
			System.out.println("Error:invalid percentage");
			return;
		}
		this.discountPercentage = discountPercentage;
	}

	/**
	 * Method to set the cycle of the cycle pass
	 * 
	 * @param cycle to be established
	 */
	public void setCycle(Cycle cycle) {
		if (cycle == null) {
			System.out.println("Error:invalid cycle");
			return;
		}
		this.cycle = cycle;
	}

	/**
	 * Method that get all the events available in a cycle pass
	 * 
	 * @param list with all the events of the cycle
	 * @return arraylist with all the available events in a cycle pass
	 */
	public ArrayList<Event> setCanGoToList(ArrayList<Event> list) {
		if (list == null) {
			System.out.println("Error:invalid list");
			return null;
		}
		ArrayList<Event> events = new ArrayList<Event>();
		for (Event e : list) {
			if (e instanceof Cycle) {
				for (Event e1 : this.setCanGoToList(((Cycle) e).getEvents())) {
					events.add(e1);
				}
			} else {
				events.add(e);
			}
		}
		return events;
	}

	/**
	 * Method to get the discount of the cycle pass
	 * 
	 * @return an int with the percentage
	 */
	public int getDiscountPercentage() {
		return this.discountPercentage;
	}

	/**
	 * Method to get the cycle of the cycle pass
	 * 
	 * @return the cycle of the cycle pass
	 */
	public Cycle getCycle() {
		return this.cycle;
	}

	/**
	 * Method to get the available events that the user can go to
	 * 
	 * @return an array list with all these events
	 */
	public ArrayList<Event> getCanGoToList() {
		return this.canGoTo;
	}

	/**
	 * Method to add an event to the events that the user has already gone
	 * 
	 * @param the event that has been attended
	 */
	public void addAlreadyAttended(Event event) {
		if (event == null) {
			System.out.println("Error:invalid event");
		}
		for (Event e : this.getCanGoToList()) {
			if (e.equals(event)) {
				this.canGoTo.remove(e);
				super.addAlreadyAttended(event);
				return;
			}
		}
	}

	/**
	 * Method to calculate the discounted price of a cycle pass
	 * 
	 * @return double with the discounted price
	 */
	public double calculateDiscountedPrice() {
		double total;
		total = this.cycle.calculateSumPrice(this.getZone());
		return ((100 - this.discountPercentage) * total / 100);
	}

	/**
	 * Method to get the name of the cycle pass
	 * 
	 * @return the name of the cycle pass
	 */
	@Override
	public String getName() {
		return (this.name);
	}

	
	/**
	 * Method to get the ending date of the pass
	 * 
	 * @return localdate with the ending date
	 */
	@Override
	public Pass copyPass(){
		CyclePass copyCP = new CyclePass(this.getName(), this.getDiscountPercentage(), this.getZone(), this.getCycle());
		return copyCP;
	}
	
	
	/**
	 * Changes the pass attributes
	 * 
	 * @param n with the new name
	 * @param disc with the new discount
	 * @param z with the new zone 
	 *
	 */
	public void changePass(String n, int disc, Zone z) {
		this.name=n;
		this.discountPercentage=disc;
		super.setZone(z);
		
	}
}
