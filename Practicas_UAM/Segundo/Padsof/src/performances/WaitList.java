package performances;

import java.util.*;
import users.*;

import java.io.*;
/**
 * This is a class that allow us to create a waitlist
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class WaitList implements Serializable{
	private List<Customer> customers;
	private Performance performance;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param performance where the waitlist is stored
	 */
	public WaitList(Performance performance) {
		if (performance == null) {
			System.out.println("Error: WaitList constructor recieves a null performance\n");
			return;
		}
		this.customers = new ArrayList<>();
		this.performance = performance;
	}

	/**
	 * Method to subscribe to a waitlist
	 * 
	 * @param customer that wants to join the waitlist
	 */
	public void subscribeToWaitList(Customer customer) {
		if (customer == null) {
			System.out.println("Error: subscribeToWaitList method in WaitList recieves a null customer\n");
			return;
		}
		this.customers.add(customer);
	}

	/**
	 * Method to unsubscribe to a waitlist
	 * 
	 * @param customer that wants to leave the waitlist
	 */
	public void unsubscribeOfWaitList(Customer customer) {
		if (customer == null) {
			System.out.println("Error: unsubscribeOfWaitList method in WaitList recieves a null customer\n");
			return;
		}
		this.customers.remove(customer);
	}

	/**
	 * Method to get the performance of the waitlist
	 * 
	 * @return performance of the waitlist
	 */
	public Performance getPerformance() {
		return this.performance;
	}

	/**
	 * Method to get all the customer of the waitlist
	 * 
	 * @return list with all the users of the waitlist
	 */
	public List<Customer> getCustomers() {
		return this.customers;
	}

}
