package users;

import events.*;

import performances.*;
import java.util.*;

import javax.persistence.*;

/**
 * This is a class that allow us to create a customer
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class Customer extends RegisteredUser {

	private ArrayList<Ticket> tickets;
	private ArrayList<Pass> passes;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param username string with the username of the customer
	 * @param password String with the password of the customer
	 */
	public Customer(String username, String password) {
		super(username, password);
		this.passes = new ArrayList<Pass>();
		this.tickets = new ArrayList<Ticket>();
	}

	/**
	 * Method to get a list with the passes of the customer
	 * 
	 * @return arraylist with the customer passes
	 */
	public ArrayList<Pass> getPasses() {
		return this.passes;
	}

	/**
	 * Method to get a list with the tickets of the customer
	 * 
	 * @return arraylist with the customer tickets
	 */
	public ArrayList<Ticket> getTickets() {
		ArrayList<Ticket> passedBookings = new ArrayList<Ticket>();
		for(Ticket t : this.tickets){
			if(t.getBookedTicket()!=null){
				if(t.getBookedTicket().checkOutOfTime()==true){
					passedBookings.add(t);
				}
			}
		}
		for(Ticket t : passedBookings){
			this.removeTicket(t);
		}
		return this.tickets;
	}

	/**
	 * Method to add a passs to the list of passes
	 * 
	 * @param pass to be added
	 */
	public void addPass(Pass pass) {
		if (pass == null) {
			System.out.println("Error: addPass method in Custommer recieves a null argument\n");
			return;
		}
		this.passes.add(pass);
	}

	/**
	 * Method to remove a passs to the list of passes
	 * 
	 * @param pass to be removed
	 */
	public void removePass(Pass pass) {
		if (pass == null) {
			System.out.println("Error: removePass method in Custommer recieves a null argument\n");
			return;
		}
		this.passes.remove(pass);
	}

	/**
	 * Method to remove a ticket to the list of passes
	 * 
	 * @param ticket to be removed
	 */
	public void removeTicket(Ticket ticket) {
		if (ticket == null) {
			System.out.println("Error: removeTicket method in Custommer recieves a null argument\n");
			return;
		}
		this.tickets.remove(ticket);
	}

	/**
	 * Method to add a ticket to the list of passes
	 * 
	 * @param ticket to be added
	 */
	public void addTicket(Ticket ticket) {
		if (ticket == null) {
			System.out.println("Error: addTicket method in Custommer recieves a null argument\n");
			return;
		}
		this.tickets.add(ticket);
	}
	/**
	 * Method to get a pass given a name
	 * 
	 * @param passName name of the pass
	 * @return pass
	 */
	public Pass getPass(String passName) {
		if (passName.isBlank()) {
			System.out.println("Error: getPass receives wrong argument");
			return null;
		}
		for(Pass p : this.passes) {
			if(p.getName().equals(passName)) {
				return p;
			}
		}
		return null;
	}
	
	/**
	 * Method that returns requested ticket
	 * @param ticketCode with the code of the ticket
	 * @return ticket
	 */
	public Ticket getTicket(int ticketCode) {
		if (ticketCode < 0 ) {
			System.out.println("Error: getTicket receives wrong argument");
			return null;
		}
		for(Ticket t : this.tickets) {
			if(t.getCode() == ticketCode) {
				return t;
			}
		}
		return null;
	}
	
	/**
	 * Method that returns the annual pass of the user
	 *
	 * @return annual pass of the customer
	 */
	public Pass getAnnualPass() {
		for(Pass p : this.getPasses()){
			if(p instanceof AnnualPass){
				return p;
			}
		}
		return null;
	}

}
