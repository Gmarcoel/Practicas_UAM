package performances;

import zones.*;

import java.time.format.DateTimeFormatter;
import es.uam.eps.padsof.tickets.*;

/**
 * This is an interface class that generates a ticket pdf
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
class TicketPDF implements ITicketInfo {
	Ticket t;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param t ticket to be printed
	 */
	public TicketPDF(Ticket t) {
		this.t = t;
	}

	/**
	 * Method to get the id of the ticket
	 * 
	 * @return int with the id of the ticket
	 */
	public int getIdTicket() {
		return this.t.getCode();
	}

	/**
	 * Method to get the name of the theater
	 * 
	 * @return String with the name of the theater
	 */
	public String getTheaterName() {
		return "THEACEPTION";
	}

	/**
	 * Method to get the name of the event
	 * 
	 * @return String with the name of the event
	 */
	public String getEventName() {
		return this.t.getPerformance().getEventTitle();
	}

	/**
	 * Method to get the date of the performance
	 * 
	 * @return String with the date of the performance
	 */
	public String getEventDate() {
		final DateTimeFormatter formatter = DateTimeFormatter.ISO_DATE_TIME;
		String formattedDateTime = this.t.getPerformance().getDate().format(formatter);
		return formattedDateTime;
	}

	/**
	 * Method to get the number of the seat
	 * 
	 * @return string with the number of the seat
	 */
	public String getSeatNumber() {
		if (this.t.getZone() instanceof SittingZone) {
			return "Zone " + this.t.getZone().getName() + ", Row " + this.t.getSeat().getNRow() + ", Column "
					+ this.t.getSeat().getNColumn();

		} else if (this.t.getZone() instanceof StandingZone) {
			return "Standing in Zone " + this.t.getZone().getName();
		}
		return "";
	}

	/**
	 * Method to get the picture of the pdf
	 * 
	 * @return string with the location of the image
	 */
	public String getPicture() {
		return "./pictures/picture.png";
	} // jpg, gif and png formats are supported
}
