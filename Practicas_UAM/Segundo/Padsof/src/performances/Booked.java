package performances;

import java.io.*;
import java.time.*;

import javax.persistence.*;

/**
 * This is an class that allow us to define if a ticket is booked
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class Booked implements Serializable{
	private LocalDateTime TTP;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param TTP time to pay the ticket
	 */
	public Booked(LocalDateTime TTP) {
		if (TTP == null) {
			System.out.println("Error: Booked constructor recieves a null TTP\n");
			return;
		}
		this.TTP = TTP;
	}

	/**
	 * Function to get the time to pay the ticket
	 * 
	 * @return a localdate with the ttp of the booked class
	 */
	public LocalDateTime getTTP() {
		return this.TTP;
	}

	/**
	 * Function to check if the if the booking is out of time
	 * 
	 * @return boolean if the booking is out of time
	 */
	public boolean checkOutOfTime() {
		if (LocalDateTime.now().isAfter(TTP)) {
			return true;
		}
		return false;
	}

}
