package statistics;

import javax.persistence.*;
import events.Event;
import performances.*;
import zones.Zone;
import java.util.*;

/**
 * This is a class that allow us to crete the statistic of a performance
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class PerformanceStatistic extends Statistic {
	private Performance performance;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param name        of the statistic
	 * @param performance performance of the corresponding statistic
	 */
	public PerformanceStatistic(String name, Performance performance) {
		super(name, 0, 0);
		if (performance == null) {
			System.out.println("Error: PerformanceStatistic constructor recieves a null performance\n");
			return;
		}
		this.performance = performance;
	}

	/**
	 * Method that updates the statistics of a performance
	 * 
	 * @param event       of the corresponing performance
	 * @param performance for which we want to update the statistic
	 */
	public void updateStatistics(Event event, Performance performance) {
		double all = 0;
		double oc = 0;
		int max = 0;
		ArrayList<Zone> zones = new ArrayList<>();
		for (Zone z : performance.getZones()) {
			zones.add(z);
		}
		for (Zone z : zones) {
			all += calculateProfit(z, performance);
			oc += z.getAttendees();
			max += z.getNPosPeople();
		}

		this.profits = all;
		this.occupancy = (oc / max) * 100;
	}

	/**
	 * Method to get the performance of the statistic
	 * 
	 * @return performance of the statistic
	 */
	public Performance getPerformance() {
		return this.performance;
	}
}
