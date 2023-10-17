package zones;

import java.io.*;
import java.time.LocalDate;

/**
 * This is a class that allow us to create a maintenance in a seat
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class MaintenanceSeat implements Serializable {
	private LocalDate endDate;
	private String notes;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param endDate  with the end of the maintenance
	 * @param notes string with the information about the maintenance
	 */
	public MaintenanceSeat(LocalDate endDate, String notes) {
		if (endDate == null || endDate.isBefore(LocalDate.now())) {
			System.out.println("Error: Invalid date\n");
			return;
		}
		this.endDate = endDate;
		this.notes = notes;
	}

	/**
	 * Method to set a new date for the end of the maintenance
	 * 
	 * @param endDate of the maintenance
	 */
	public void setDate(LocalDate endDate) {
		if (endDate == null || endDate.isBefore(LocalDate.now())) {
			System.out.println("Error: Invalid date\n");
			return;
		}
		this.endDate = endDate;
		return;
	}

	/**
	 * Method to set a new reason for the maintenance
	 * 
	 * @param notes of the maintenance
	 */
	public void setNotes(String notes) {
		this.notes = notes;
		return;
	}

	/**
	 * Method to get the reason of the maintenance
	 * 
	 * @return string with the notes of the maintenance
	 */
	public String getNotes() {
		return this.notes;
	}

	/**
	 * Method to get the end date of the maintenance
	 * 
	 * @return localdate with the end date
	 */
	public LocalDate getEndDate() {
		return this.endDate;
	}

	/**
	 * Method that checks if a maintenance is still vigent
	 * 
	 * @return boolean if the maintenance is vigent
	 */
	public boolean maintainedSeatVigent() {
		if (this.endDate.isBefore(LocalDate.now())) {
			return false;
		}
		return true;
	}
}
