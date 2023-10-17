package performances;

import javax.persistence.*;

import events.*;
import zones.*;
import java.util.*;
import java.io.Serializable;
import java.time.*;


/**
 * This is a class that allow us to create a performance
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier LÃ³pez de la Nieta LujÃ¡n
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class Performance implements Serializable{
	private LocalDateTime date;
	private ArrayList<Zone> availableZones;
	private ArrayList<Ticket> tickets;
	private Event event;
	private WaitList waitList;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param date  of the performance
	 * @param zones to be copied in the performance to occupy them
	 * @param event corresponded to the performance
	 */
	public Performance(LocalDateTime date, ArrayList<Zone> zones, Event event) {
		if (date == null || zones == null || event == null) {
			System.out.println("Error: Performance constructor recieves a null attribute\n");
			return;
		}
		this.availableZones = new ArrayList<>();
		this.tickets = new ArrayList<>();
		for (Zone z : zones) {
			this.availableZones.add(z.cloneZone());
		}
		this.date = date;
		this.event = event;
		this.waitList = new WaitList(this);
	}

	/**
	 * Method to postpone a performance
	 * 
	 * @param date to establish in the performance
	 */
	public void postponePerformance(LocalDateTime date) {
		if (date == null) {
			System.out.println("Error: postponePerformance method in Performance recieves a null date\n");
			return;
		}
		if (date.isBefore(this.getDate())) {
			System.out.println("Error: postponePerformance method in Performance recieves an invalid date\n");
			return;
		}

		this.date = date;
	}

	/**
	 * Method to get the modified zone of the performance
	 * 
	 * @param z that we want to get the copy of
	 * 
	 * @return the zone if it finds it null if not
	 */
	public Zone getZone(Zone z) {
		if (z == null) {
			System.out.println("Error: getZone method in Performance recieves a null zone\n");
			return null;
		}
		for (Zone zone : this.getZones()) {
			if (zone instanceof FragmentedZone) {
				if (((FragmentedZone) zone).getSubZone(z.getName()) != null) {
					return ((FragmentedZone) zone).getSubZone(z.getName());
				}
			}
			if (zone.getName() == z.getName()) {
				return zone;
			}
		}
		System.out.println("Error: getZone method in Performance recieves an inexistent zone\n");
		return null;
	}

	/**
	 * Method to check if a seat of a zone is occupied
	 * 
	 * @param zone where we want to see if it is occupied
	 * @param seat that we want to check if it is occupied
	 * @return boolean if is occupied
	 */
	public boolean checkOccupied(Zone zone, Seat seat) {
		if (zone == null || seat == null) {
			System.out.println("Error: checkOccupied(Zone, Seat) method in Performance recieves a null attribute\n");
			return true;
		}
		for (Zone z : this.availableZones) {
			if (z instanceof FragmentedZone) {
				if (!((FragmentedZone) z).isOccupied(zone, seat)) {
					return false;
				}
			}
			if (z.getName().equals(zone.getName())) {
				return ((SittingZone) z).isOccupied(seat);
			}
		}
		return true;
	}

	/**
	 * Method to check if a standing zone is occupied
	 * 
	 * @param zone where we want to see if it is occupied
	 * @return boolean if is occupied
	 */
	public boolean checkOccupied(Zone zone) {
		if (zone == null) {
			System.out.println("Error: checkOccupied(Zone) method in Performance recieves a null zone\n");
			return true;
		}
		for (Zone z : availableZones) {
			if (z instanceof FragmentedZone) {
				if (!((FragmentedZone) z).isOccupied(zone))
					return false;
			}
			if ((z).getName().equals(zone.getName())) {
				return ((StandingZone) z).isOccupied();
			}
		}
		return true;

	}

	/**
	 * Method to create a ticket depending on the zone and the seat
	 * 
	 * @param zone where we want to buy the ticket
	 * @param seat where we want to buy the ticket
	 * @return ticket that has been created
	 */
	public Ticket selectTicket(Zone zone, Seat seat) {
		if (zone == null || seat == null) {
			System.out.println("Error: selectTicket(Zone, Seat) method in Performance recieves a null attribute\n");
			return null;
		}

		if (!checkOccupied(zone, seat)) {
			Ticket ticket = new Ticket(zone, seat, this);
			this.tickets.add(ticket);
			return ticket;
		}
		return null;
	}

	/**
	 * Method to select a ticket by the name of the zone
	 * 
	 * @param zone where we want to buy the ticket
	 * @param nRow row of the zone to buy the ticket
 	 * @param nColumn column of the zone to buy the ticket
	 * @return ticket that has been created
	 */
	public Ticket selectTicketWithString(String zone, int nRow, int nColumn) {
		if (zone == null) {
			System.out.println("Error: selectTicket(Zone, Seat) method in Performance recieves a null attribute\n");
			return null;
		}

		
		if (!checkOccupied(this.getZone(zone), ((SittingZone)this.getZone(zone)).getSeat(nRow, nColumn))) {
			Ticket ticket = new Ticket(this.getZone(zone), ((SittingZone)this.getZone(zone)).getSeat(nRow, nColumn), this);
			this.tickets.add(ticket);
			return ticket;
		}
		return null;
	}

	/**
	 * Method to get a zone given the name
	 * 
	 * @param zName name of the required zone
	 * @return zone requested
	 */
	public Zone getZone(String zName){
		for(Zone z : this.getZones()){
			if(z.getName().equals(zName)){
				return z;
			}
			else if (z instanceof FragmentedZone){
				if(((FragmentedZone)z).getSubZone(zName)!=null){
					return ((FragmentedZone)z).getSubZone(zName);
				}
			}
		}
		return null;
	}

	/**
	 * Method to delete a ticket of a performace
	 * 
	 * @param t ticket that we want to eliminate
	 */
	public void cancelPerformanceTicket(Ticket t) {
		if (t == null) {
			System.out.println("Error: cancelPerformanceTicket method in Performance recieves a null ticket\n");
			return;
		}
		t.freeTicket();
		this.tickets.remove(t);
	}

	/**
	 * Method to create a ticket depending on the zone
	 * 
	 * @param zone where we want to buy the ticket
	 * @return ticket that has been created
	 */
	public Ticket selectTicket(Zone zone) {
		if (zone == null) {
			System.out.println("Error: selectTicket(Zone) method in Performance recieves a null zone\n");
			return null;
		}

		if (!checkOccupied(zone)) {
			Ticket ticket = new Ticket(zone, this);
			this.tickets.add(ticket);
			return ticket;
		}
		return null;
	}
	
	/**
	 * Method to select a ticket given the name of the zone
	 * 
	 * @param zone name of the zone to buy the ticket
	 * @return ticket that has been created
	 */
	public Ticket selectTicketWithString(String zone) {
		if (zone == null) {
			System.out.println("Error: selectTicket(Zone) method in Performance recieves a null zone\n");
			return null;
		}

		if (!checkOccupied(this.getZone(zone))) {
			Ticket ticket = new Ticket(this.getZone(zone), this);
			this.tickets.add(ticket);
			return ticket;
		}
		return null;
	}

	/**
	 * Method to get the date of the performance
	 * 
	 * @return the date of the performance
	 */
	public LocalDateTime getDate() {
		return this.date;
	}

	/**
	 * Method to get the modified zones of the performance
	 * 
	 * @return list with the modified zones
	 */
	public List<Zone> getZones() {
		return this.availableZones;
	}

	/**
	 * Method to get the event of the performance
	 * 
	 * @return event of the performance
	 */
	public Event getEvent() {
		return this.event;
	}

	/**
	 * Method to get the title of the event
	 * 
	 * @return string with the event title
	 */
	public String getEventTitle() {
		return this.event.getTitle();
	}

	/**
	 * Method to get the waitlist of the performance
	 * 
	 * @return waitlist of the performance
	 */
	public WaitList getWaitList() {
		return this.waitList;
	}

	/**
	 * Method to check if there are available tickets for the performance
	 * 
	 * @return boolean if the performance is full
	 */
	public boolean checkIfFull() {
		boolean full = false;
		for (Zone z : this.getZones()) {
			if (z.getOccupancy() < 1) {
				full = true;
			}
		}
		return full;
	}

}