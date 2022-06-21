package statistics;

import java.io.*;

import javax.persistence.*;
import zones.FragmentedZone;
import performances.Performance;
import zones.*;

/**
 * This is an abstract class that allow us to define a statistic
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public abstract class Statistic implements Serializable {
	private String name;
	protected double occupancy;
	protected double profits;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param name      of the zone corresponding with the statistic
	 * @param occupancy of the corresponding zone
	 * @param profits   of the zone
	 */
	public Statistic(String name, double occupancy, double profits) {
		if (name == null || occupancy < 0 || profits < 0) {
			System.out.println("Error: Statistic constructor recieves an incorrect argument\n");
			return;
		}
		this.name = name;
		this.occupancy = occupancy;
		this.profits = profits;
	}

	/**
	 * Method to get the name of the statistic
	 * 
	 * @return string with the name of the statistic
	 */
	public String getName() {
		return this.name;
	}

	/**
	 * Method to get the occupancy of the statistic
	 * 
	 * @return double with the occupancy
	 */
	public double getOccupancy() {
		return occupancy;
	}

	/**
	 * Method to get the profits of the statistic
	 * 
	 * @return double with the profits
	 */
	public double getProfits() {
		return profits;
	}

	/**
	 * Method to calculate the profit of the performance
	 * 
	 * @param zone with the zone
	 * @param performance with the performance
	 * 
	 * @return double with the calculated price
	 */
	public double calculateProfit(Zone zone, Performance performance) {
		double p = 0;
		Zone aux = null;
		if (zone == null || performance == null) {
			System.out.println("Error: invalid argument\n");
			return -1;
		}
		if (zone instanceof FragmentedZone) {
			for (Zone sz : ((FragmentedZone) zone).getSubZones()) {
				p += calculateProfit(sz, performance);
			}
			return p;
		}
		aux = performance.getZone(zone);
		p = performance.getEvent().getPrice(zone) * aux.getAttendees();
		return p;
	}
}
