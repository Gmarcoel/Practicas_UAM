package statistics;

import events.*;
import performances.Performance;
import zones.Zone;
import java.util.*;

import javax.persistence.*;

/**
 * This is a class that allow us to create an statistic of a event
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class EventStatistic extends Statistic {
	Event event;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param name string with the name of the statistic 
	 * @param event from which the statistic will be made
	 */
	public EventStatistic(String name, Event event) {
		super(name, 0, 0);
		if (event == null) {
			System.out.println("Error: EventStatistic constructor recieves a null event\n");
			return;
		}
		this.event = event;
	}

	/**
	 * Method that updates the statistics of an event
	 * 
	 * @param event for wich we want to update the statistics
	 */
	public void updateStatistics(Event event) {
		int n = 0;
		double all = 0;
		double oc = 0;
		int max = 0;
		Zone aux = null;

		if (event == null) {
			System.out.println("Error: updateStatistics method in EventStatistic recieves a null attribute\n");
			return;
		}

		for (Performance performance : event.getPerformances()) {
			for (Zone z : performance.getZones()) {
				all += calculateProfit(z, performance); 
				oc += z.getAttendees();
				max += z.getNPosPeople();
			}

		}

		this.profits = all;
		this.occupancy = (oc / max) * 100;
	}

	/**
	 * Method to get the corresponding event of the statistic
	 * 
	 * @return event of the statistic
	 */
	public Event getEvent() {
		return event;
	}

}
