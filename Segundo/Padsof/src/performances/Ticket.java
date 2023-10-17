package performances;

import javax.persistence.*;
import java.io.*;
import es.uam.eps.padsof.tickets.*;

import zones.*;

/**
 * This is a class that allow us to create a ticket
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class Ticket implements Serializable {
	private Zone zone;
	private Seat seat;
	private boolean purchased;
	private Booked bookedTicket = null;
	private Performance performance;
	private int code;
	static int counter=0;
	/**
	 * Constructor, with the attributes
	 * 
	 * @param zone        of the ticket
	 * @param seat        of the ticket
	 * @param performance of the ticket
	 */
	public Ticket(Zone zone, Seat seat, Performance performance) {
		if (zone == null || seat == null || performance == null) {
			System.out.println("Error: Ticket(Zone, Seat, Performance) constructor recieves a null attribute\n");
			return;
		}
		this.zone = zone;
		this.seat = seat;
		this.performance = performance;
		this.code = generateCode();
		counter++;
	}

	/**
	 * Constructor, with the attributes
	 * 
	 * @param zone        of the ticket
	 * @param performance of the ticket
	 */
	public Ticket(Zone zone, Performance performance) {
		if (zone == null || performance == null) {
			System.out.println("Error: Ticket(Zone, Performance) constructor recieves a null attribute\n");
			return;
		}
		this.zone = zone;
		this.seat = null;
		this.performance = performance;
		counter++;
	}

	/**
	 * Method to set a booking to a ticket
	 * 
	 * @param bookedTicket of the booking
	 */
	public void setBookedTicket(Booked bookedTicket) {
		if (bookedTicket != null) {
			if (this.getZone() instanceof SittingZone) {
				((SittingZone) this.getZone()).occupy(this.getSeat());
			} else if (this.getZone() instanceof StandingZone) {
				((StandingZone) this.getZone()).occupy();
			}
		}
		this.bookedTicket = bookedTicket;
	}

	/**
	 * Method to get the zone of the ticket
	 * 
	 * @return zone of the ticket
	 */
	public Zone getZone() {
		return this.zone;
	}

	/**
	 * Method to get the seat of the ticket
	 * 
	 * @return seat of the ticket
	 */
	public Seat getSeat() {
		return this.seat;
	}

	/**
	 * Method to check if the ticket has been purchased
	 * 
	 * @return boolean if the ticket has been purchased
	 */
	public boolean getPurchased() {
		return this.purchased;
	}

	/**
	 * Method to get the booking of the ticekt
	 * 
	 * @return booked of the ticket
	 */
	public Booked getBookedTicket() {
		return this.bookedTicket;
	}

	/**
	 * Method to get the performance of the ticket
	 * 
	 * @return performance corresponding to the ticket
	 */
	public Performance getPerformance() {
		return this.performance;
	}

	/**
	 * Method to set the purchased attribute to a ticket
	 * 
	 * @param b if the ticket has been purchased
	 */
	public void setPurchased(boolean b) {
		if (this.bookedTicket == null) {
			if (this.getZone() instanceof SittingZone) {
				((SittingZone) this.getZone()).occupy(this.getSeat());
			} else if (this.getZone() instanceof StandingZone) {
				((StandingZone) this.getZone()).occupy();
			}
		}
		this.setBookedTicket(null);
		this.purchased = b;
	}

	/**
	 * Method to free all the space taken by the ticket in a performance
	 */
	public void freeTicket() {
		if (this.zone instanceof SittingZone) {
			((SittingZone) zone).free(this.seat);
		} else if (this.zone instanceof StandingZone) {
			((StandingZone) zone).free();
		}
	}

	/**
	 * Method to generate a unique code for the ticket
	 * 
	 * @return int with the code
	 */
	public int generateCode() {
		int result = this.performance.getDate().getYear()*10000;
		result=result+(this.performance.getDate().getMonthValue()*100);
		result=result+(this.performance.getDate().getDayOfMonth());
		result=result+counter;
		/*String aux;
		if (this.zone instanceof SittingZone) {
			aux = this.performance.getEventTitle() + this.zone.getName() + this.getSeat().getNRow()
					+ this.getSeat().getNColumn() + this.performance.getDate();
		} else {
			aux = this.performance.getEventTitle() + this.zone.getName() + this.performance.getDate();
		}

		char[] z = aux.toCharArray();
		for (int i = 0; i < z.length; i++) {
			result = result + ((int) z[i]);
		}*/
		return result;
	}

	/**
	 * Method to get the cifrated code
	 * 
	 * @return int with the code
	 */
	public int getCode() {
		return this.code;
	}

	/**
	 * Method to generate a pdf with all the ticket information
	 */
	public void generateTicketPDF() {
		if(this.purchased==true){
		try {
			TicketSystem.createTicket(new TicketPDF(this), "./generatedTickets/" // Output folder
			);
		} catch (NonExistentFileException nefe) {
			System.out.println(nefe);
			return;
		} catch (UnsupportedImageTypeException nefe) {
			System.out.println(nefe);
			return;
		}
		}
		else {
			System.out.println("Cant download a ticket that you havent purchased");
		}
	}
}
