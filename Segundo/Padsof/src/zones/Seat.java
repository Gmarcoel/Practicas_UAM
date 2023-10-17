package zones;

import java.io.*;
import java.time.LocalDate;

/**
 * This is a class that allow us to create a seat
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class Seat implements Serializable {

	private boolean occupied;
	private int nRow;
	private int nColumn;
	private boolean available;
	private MaintenanceSeat mSeat;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param nRow    int with the number of row of the seat
	 * @param nColumn int with the number of column of the seat
	 */
	public Seat(int nRow, int nColumn) {
		if (nRow < 0) {
			System.out.println("Error: Negative Row\n");
			return;
		}
		if (nColumn < 0) {
			System.out.println("Error: Negative Column\n");
			return;
		}
		this.nRow = nRow;
		this.nColumn = nColumn;
		this.occupied = false;
		this.available = true;
		this.mSeat = null;
	}

	/**
	 * Method to set the occupied value to the seat
	 * 
	 * @param b to set the occupied value
	 */
	public void setOccupied(boolean b) {

		this.occupied = b;
	}

	/**
	 * Method to set the seat available
	 * 
	 * @param b to set the occupied value
	 */
	public void setAvailable(boolean b) {
		this.available = b;
	}

	/**
	 * Method to get the row of the seat
	 * 
	 * @return int with the row
	 */
	public int getNRow() {
		return this.nRow;
	}

	/**
	 * Method to get the column of the seat
	 * 
	 * @return int with the column
	 */
	public int getNColumn() {
		return this.nColumn;
	}

	/**
	 * Method to get the availability of the seat
	 * 
	 * @return boolean if the seat is available
	 */
	public boolean getAvailable() {
		return this.available;
	}

	/**
	 * Method to check if the seat is occupied
	 * 
	 * @return boolean if the seat is occupied
	 */
	public boolean getOccupied() {
		if(getAvailable()==false){
				return false;

		} 
		else if (getMSeat()!=null){
			if(getMSeat().maintainedSeatVigent()){
				return true;
			}
			else{
				habilitateSeat();
			}
		}
		return this.occupied;
	}

	/**
	 * Method to get maintenance of a seat
	 * 
	 * @return maintenanceseat with the information of the maintenance
	 */
	public MaintenanceSeat getMSeat() {
		return this.mSeat;
	}

	/**
	 * Method to start a maintenance in a seat
	 * 
	 * @param date  with the end of the maintenance
	 * @param notes of the maintenance
	 */
	public void maintainSeat(LocalDate date, String notes) {
		if (date == null) {
			System.out.println("Error: Invalid date\n");
			return;
		}
		this.mSeat = new MaintenanceSeat(date, notes);
	}

	/**
	 * Method to habilitate a seat after a maintenance
	 */
	public void habilitateSeat() {
		this.mSeat = null;
	}
}
