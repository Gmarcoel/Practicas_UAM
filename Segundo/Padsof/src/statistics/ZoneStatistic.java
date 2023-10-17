package statistics;

import javax.persistence.*;
import zones.*;

import events.*;
import performances.Performance;

import java.util.*;

/**
 * This is an abstract class that allow us to create a statistic of a zone
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class ZoneStatistic extends Statistic {
	private Zone zone;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param name string with the name of the statistic
	 * @param zone of the statistic
	 */
	public ZoneStatistic(String name, Zone zone) {
		super(name, 0, 0);
		if (zone == null) {
			System.out.println("Error: ZoneStatistic constructor recieves a null zone\n");
			return;
		}
		this.zone = zone;
	}

	/**
	 * Method that updates the statistics of a performance
	 * 
	 * @param event       of the corresponding performance
	 * @param performance for wich we want to update the statistics
	 * @param zone        that we want to update the statistics of
	 */
	public void updateStatisticsFromPerformance(Event event, Performance performance, Zone zone) {
		if (zone == null || performance == null || event == null) {
			System.out.println("Error: updateStatisticsFromPerformance in ZoneStatistic recieves a null attribute\n");
			return;
		}
		this.profits = 0;
		Zone goodZone = null;
		goodZone = performance.getZone(zone);
		this.occupancy = ((double) goodZone.getAttendees() / goodZone.getNMaxPeople()) * 100;
		this.profits = calculateProfit(zone, performance);
	}

	/**
	 * Method that updates the statistics of an event
	 * 
	 * @param event for which we want to update the statitics
	 * @param zone  that we want to update the statistics of
	 */
	public void updateStatisticsFromEvent(Event event, Zone zone) {

		double all = 0;
		double oc = 0;
		int max = 0;
		Zone aux = null;
		if (zone == null || event == null) {
			System.out.println("Error: updateStatisticsFromEvent in ZoneStatistic recieves a null attribute\n");
			return;
		}

		for (Performance performance : event.getPerformances()) {

			aux = performance.getZone(zone);
			all += this.calculateProfit(zone, performance);
			max += zone.getNPosPeople();
			oc += aux.getAttendees();

		}
		this.profits = all;
		this.occupancy = (oc / max) * 100;
	}

	/**
	 * Method that updates the statistics of all the events in a zone
	 * 
	 * @param events for which we want to update the statitics
	 * @param zone   that we want to update the statistics of
	 */
	public void updateStatistics(List<Event> events, Zone zone) {
		double all = 0;
		double oc = 0;
		int max = 0;
		Zone z = null;
		ArrayList<Zone> thisZones = new ArrayList<>(); 
		ArrayList<Event> thisEvents = new ArrayList<>();

		if (zone == null || events == null) {
			System.out.println("Error: updateStatistics in ZoneStatistic recieves a null attribute\n");
			return;
		}

		for (Event event : events) {
			if (!(event instanceof Cycle)) {

				for (Performance performance : event.getPerformances()) { //
					z = performance.getZone(zone);
					all += calculateProfit(zone, performance);
					oc += z.getAttendees();
					max += z.getNPosPeople();
				}
			}
		}
		this.profits = all;

		this.occupancy = (oc / max) * 100;
	}

	/**
	 * Method to get the zone of the statistics
	 * 
	 * @return zone of the statistics
	 */
	public Zone getZone() {
		return this.zone;
	}
}
