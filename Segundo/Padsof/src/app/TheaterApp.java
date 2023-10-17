package app;

import es.uam.eps.padsof.telecard.*;
import java.io.*;
import java.time.*;
import java.util.*;
import users.*;
import zones.*;
import performances.*;
import statistics.*;
import events.*;

/**
 * This is a class that allow us to create the main application
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier LÃ³pez de la Nieta LujÃ¡n
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class TheaterApp implements Serializable {
	private ArrayList<Zone> zones;
	private ArrayList<Event> events;
	private ArrayList<RegisteredUser> users;
	private ArrayList<Pass> passes;
	private ArrayList<Statistic> statistics;
	public int ttp;
	public int ttb;
	public ArrayList<Price> annualPassPrice;

	/**
	 * Constructor with no attributes, we inititialize everything inside
	 */
	public TheaterApp() {
		this.ttb = 0;
		this.ttp = 0;
		this.annualPassPrice = new ArrayList<>();
		this.zones = new ArrayList<>();
		this.events = new ArrayList<>();
		this.users = new ArrayList<>();
		this.passes = new ArrayList<>();
		this.statistics = new ArrayList<>();
	}

	/**
	 * Method to set the price of an annual pass in a zone
	 * 
	 * @param p price of the annual pass
	 * @param z zone where you want to apply that price
	 */
	public void setAnnualPassPrice(double p, Zone z) {
		if (p < 0) {
			System.out.println("Error:Invalid price\n");
			return;
		}
		if (z == null) {
			System.out.println("Error:Invalid zone\n");
			return;
		}
		for (Price i : this.annualPassPrice) {
			if (i.getZone().equals(z)) {
				i.setPrice(p);
				return;
			}
		}
	}

	/**
	 * Method to get the price of an annual pass in a zone
	 * 
	 * @param z zone which you want to get the price of the annual pass
	 * @return double with the price of the annual pass
	 */
	public double getAnnualPassPrice(Zone z) {
		if (z == null) {
			System.out.println("Error:Invalid zone\n");
			return -1;
		}

		for (Price i : this.annualPassPrice) {
			if (i.getZone().equals(z)) {
				return i.getPrice();
			}
		}
		return 0;
	}

	/**
	 * Method that allow a customer to pay a ticekt with a credit card
	 * 
	 * @param c          customer who whants to buy the ticket
	 * @param e          event that the customer want to go
	 * @param t          ticket that the customer wants to buy
	 * @param cardNumber string containing the credit card number
	 * @return boolean if the operation has been done successfully
	 */
	public boolean payTicketWithCard(Customer c, Event e, Ticket t, String cardNumber) {
		if (c == null || e == null || t == null) {
			System.out.println("Error:The ticket or the event has't been selected\n");
			return false;
		}
		if (this.checkCard(cardNumber)) {
			try {
				TeleChargeAndPaySystem.charge(cardNumber, e.getTitle(), e.getPrice(t.getZone()), true);
				if (t.getBookedTicket() != null) {
					this.purchaseBooked(c, t);
				} else {
					t.setPurchased(true);
					c.addTicket(t);
				}
				return true;
			} catch (NumberFormatException nfe) {
				System.out.println("Error:Unable to pay\n");
				return false;
			} catch (FailedInternetConnectionException fic) {
				System.out.println("Error:Unable to pay, check your connection\n");
				return false;
			} catch (OrderRejectedException ore) {
				System.out.println("Error:Unable to pay, Order rejected\n");
				return false;
			}
		}
		return false;
	}

	/**
	 * Method that allow a customer to pay a pass with a credit card
	 * 
	 * @param c          customer who wants to buy the pass
	 * @param p          pass that the customer wants to buy
	 * @param cardNumber string containing the credit card number
	 * @return boolean if the operation has been done successfully
	 */
	public boolean payPassWithCard(Customer c, Pass p, String cardNumber) {
		if (c == null || p == null) {
			System.out.println("Error:The pass or customer havent been selected correctly\n");
			return false;
		}
		if (this.checkCard(cardNumber)) {
			try {
				TeleChargeAndPaySystem.charge(cardNumber, p.getName(), p.getPrice(), true);
				c.addPass(p.copyPass());
				return true;
			} catch (NumberFormatException nfe) {
				System.out.println("Error:Unable to pay \n");
				return false;
			} catch (FailedInternetConnectionException fic) {
				System.out.println("Error:Unable to pay, check your connection\n");
				return false;
			} catch (OrderRejectedException ore) {
				System.out.println("Error:Unable to pay, Order rejected\n");
				return false;
			}
		}
		return false;
	}

	/**
	 * Method that allow a customer to pay a pass with a credit card
	 * 
	 * @param c          customer who wants to buy the pass
	 * @param z          zone of the requested pass
	 * @param cardNumber string containing the credit card number
	 * @return boolean if the operation has been done successfully
	 */
	public boolean payPassWithCard(Customer c, Zone z, String cardNumber) {
		if (c == null) {
			System.out.println("Error:The customer hasnt been selected correctly\n");
			return false;
		}
		if (this.checkCard(cardNumber)) {
			try {
				if (c.getAnnualPass() != null) {
					System.out.println("Customer " + c.getUsername() + " already has an annual pass\n");
					return false;
				}
				TeleChargeAndPaySystem.charge(cardNumber, "Annual Pass " + LocalDateTime.now().getYear() + "-"
						+ LocalDateTime.now().plusYears(1).getYear(), this.getAnnualPrice(z), true);
				this.createAnnualPass(c, z);
				return true;
			} catch (NumberFormatException nfe) {
				System.out.println("Error:Unable to pay \n");
				return false;
			} catch (FailedInternetConnectionException fic) {
				System.out.println("Error:Unable to pay, check your connection\n");
				return false;
			} catch (OrderRejectedException ore) {
				System.out.println("Error:Unable to pay, Order rejected\n");
				return false;
			}
		}
		return false;
	}

	/**
	 * Method to login in the application
	 * 
	 * @param username of the user who wants to login
	 * @param password of the user who wants to login
	 * @return boolean if the the user has logged successfully
	 */
	public boolean logIn(String username, String password) {
		if (username.isBlank() || password.isBlank()) {
			System.out.println("Error:Username or password not valid. The field cannot be empty\n");
			return false;
		}
		for (RegisteredUser u : this.users) {
			if (u.checkCredentials(username, password)) {
				return true;
			}
		}
		return false;
	}

	/**
	 * Method that gets the available passes of a customer to attend to an event
	 * 
	 * @param event    to check if the customer have passes to attend
	 * @param customer that has the passes to check
	 * @param t        ticket to check if the zone selected corresponds with the
	 *                 pass
	 * @return arraylist with all the available passes for the event
	 */
	public ArrayList<Pass> customerAvailablePassesForEvent(Event event, Customer customer, Ticket t) {
		if (customer == null || event == null || t == null) {
			System.out.println("Error:the customer, the event or the ticket does't exist\n");
			return null;
		}
		ArrayList<Pass> output = new ArrayList<>();
		for (Pass p : customer.getPasses()) {
			if (p instanceof CyclePass) {
				for (Event e : ((CyclePass) p).getCanGoToList()) {
					if (e == event) {
						if (t.getZone().getName() == p.getZone().getName()) {
							output.add(p);
						}
					}
				}
			} else if (p instanceof AnnualPass) {
				if (((AnnualPass) p).checkIfValidAnnualPass() == true) {
					if (p.getIfHasAlreadyAttended(event) == false) {
						if (p.getZone().getName() == t.getZone().getName()) {
							output.add(p);
						}
					}
				} else {
					customer.removePass(p);
				}
			}
		}
		return output;
	}

	/**
	 * Method that allows a customer to pay a ticket with a previously bought pass
	 * 
	 * @param c    customer that wants to get ticket using the pass
	 * @param pass that allow the user to buy the ticket
	 * @param e    event that the customer wants to attend
	 * @param t    ticket to be bought
	 * 
	 * @return boolean if the ticket has been payed successfully
	 */
	public boolean payWithPass(Customer c, Pass pass, Event e, Ticket t) {
		if (c == null || pass == null || e == null || t == null) {
			return false;
		}
		for (Pass p : customerAvailablePassesForEvent(e, c, t)) {
			if (p.getName().equals(pass.getName())) {
				if (t.getZone().getName().equals(p.getZone().getName())) {
					p.addAlreadyAttended(e);
					if (t.getBookedTicket() != null) {
						this.purchaseBooked(c, t);
					} else {
						t.setPurchased(true);
						c.addTicket(t);
					}
					return true;
				} else {
					return false;
				}
			}
		}
		return false;
	}

	/**
	 * Method that allows a user to search for an event
	 * 
	 * @param type int that depending on the value returns a different type of
	 *             events
	 * @return arraylist with the results of the search
	 */
	public ArrayList<Event> searchEvent(int type) {
		if (type < 0 || type > 2)
			return null;
		ArrayList<Event> eventsFiltered = new ArrayList<>();
		for (Event e : this.events) {
			if (e instanceof TheaterPlay && type == 0) {
				eventsFiltered.add(e);
			} else if (e instanceof Dance && type == 1) {
				eventsFiltered.add(e);
			} else if (e instanceof Concert && type == 2) {
				eventsFiltered.add(e);
			}
		}
		return eventsFiltered;
	}

	/**
	 * Method that add a pass to the app
	 * 
	 * @param pass to be added
	 */
	public void addPass(Pass pass) {
		if (pass == null)
			return;
		this.passes.add(pass);
	}

	/**
	 * Method to get the list of zones of the theater
	 * 
	 * @return arraylist with all the zones
	 */
	public ArrayList<Zone> getZones() {
		return this.zones;
	}

	/**
	 * Method to create a dance event
	 * 
	 * @param title       string with the title of the event
	 * @param author      String with the author of the event
	 * @param director    string that contains the director of the event
	 * @param description string with a short description of the event
	 * @param conductor   string with the conductor of the event
	 * @param dancer      string with the dancers of the event
	 * @param orchestra   string with the orchestra of the event
<<<<<<< HEAD
	 * @param duration with the duration of the event
=======
>>>>>>> 1cd9b5ca3eae2f21b66106514195f08a9f18320b
	 * @return boolean if the operation has been done successfully
	 */
	public boolean createDanceEvent(String title, String author, String director, String description, String conductor,
			String dancer, String orchestra, int duration) {
		if (this.checkIfEventExist(title) == true) {
			System.out.println("Error:there exists an event with that name");
			return false;
		}
		Event event = new Dance(title, author, director, description, conductor, dancer, orchestra);
		if (event == null) {
			return false;
		}
		event.setDuration(duration);
		initializePrices(event);
		this.events.add(event);
		this.statistics.add(new EventStatistic(title, event));
		return true;
	}

	/**
	 * Method to create a play event
	 * 
	 * @param title       string with the title of the event
	 * @param author      String with the author of the event
	 * @param director    string that contains the director of the event
	 * @param description string with a short description of the event
	 * @param actors      string with the actors of the event
<<<<<<< HEAD
	 * @param duration with the duration of the event
=======
>>>>>>> 1cd9b5ca3eae2f21b66106514195f08a9f18320b
	 * @return boolean if the operation has been done successfully
	 */
	public boolean createPlayEvent(String title, String author, String director, String description, String actors,
			int duration) {
		if (this.checkIfEventExist(title) == true) {
			System.out.println("Error:there exists an event with that name");
			return false;
		}
		Event event = new TheaterPlay(title, author, director, description, actors);
		if (event == null) {
			return false;
		}
		event.setDuration(duration);
		initializePrices(event);
		this.events.add(event);
		this.statistics.add(new EventStatistic(title, event));
		return true;
	}

	/**
	 * Method to create a concert event
	 * 
	 * @param title       string with the title of the event
	 * @param author      String with the author of the event
	 * @param director    string that contains the director of the event
	 * @param description string with a short description of the event
	 * @param musicPieces string with all the music pieces of the event
	 * @param orchestra   string with the orchestraof the event
<<<<<<< HEAD
	 * @param duration the duration of th eevent
=======
>>>>>>> 1cd9b5ca3eae2f21b66106514195f08a9f18320b
	 * @return boolean if the operation has been done successfully
	 */
	public boolean createConcertEvent(String title, String author, String director, String description,
			String musicPieces, String orchestra, int duration) {

		if (this.checkIfEventExist(title) == true) {
			System.out.println("Error:there exists an event with that name");
			return false;
		}
		Event event = new Concert(title, author, director, description, musicPieces, orchestra);
		if (event == null) {
			return false;
		}
		event.setDuration(duration);
		initializePrices(event);
		this.events.add(event);
		this.statistics.add(new EventStatistic(title, event));
		return true;
	}

	/**
	 * Method to initialize all the prices of an event
	 * 
	 * @param e event to initialize the prices
	 */
	public void initializePrices(Event e) {
		if (e == null) {
			System.out.println("Error:invalid event");
			return;
		}
		for (Zone z : this.zones) {
			if (z instanceof FragmentedZone) {
				initializePricesFragmented(e, z);
			} else {
				initializePrice(e, z);
			}
		}
	}

	/**
	 * Method to initialize a single price
	 * 
	 * @param e    event to initialize the price
	 * @param zone where the Price is established
	 */
	public void initializePrice(Event e, Zone zone) {
		if (e == null || zone == null) {
			System.out.println("Error:invalid event or zone");
			return;
		}
		Price p = new Price(zone);
		p.setEvent(e);
		e.addPrice(p);
	}

	/**
	 * Method to initialize the prices of a fragmented zone
	 * 
	 * @param e    event to initialize the price
	 * @param zone where you want to initialize the Prices
	 */
	public void initializePricesFragmented(Event e, Zone zone) {
		if (e == null || zone == null) {
			System.out.println("Error:invalid event or zone");
			return;
		}
		for (Zone z : ((FragmentedZone) zone).getSubZones()) {
			if (z instanceof FragmentedZone) {
				initializePricesFragmented(e, z);
			} else {
				initializePrice(e, z);
			}
		}
	}

	/**
	 * Method to cancel/delete an event
	 * 
	 * @param event to be cancelled
	 */
	public void cancelEvent(Event event) {
		if (event == null) {
			System.out.println("Error:The event doesn't exist");
			return;
		}
		this.events.remove(event);
		for (Statistic s : this.statistics) {
			if (s instanceof EventStatistic) {

				if (((EventStatistic) s).getEvent().equals(event)) {
					this.statistics.remove(s);
					break;
				}
			}
		}
	}

	/**
	 * Method that checks if an event with a given name already exists
	 * 
	 * @param name to check if the event exist
	 * @return boolean if the event already exists
	 */
	public boolean checkIfEventExist(String name) {
		if (name.isBlank()) {
			System.out.println("Error:the string is not valid");
			return true;
		}
		for (Event i : this.getEvents()) {
			if ((i instanceof Cycle) == false) {
				if (i.getTitle().equals(name)) {
					return true;
				}
			}
		}
		return false;
	}

	/**
	 * Method that checks if a cycle with a given name already exists
	 * 
	 * @param name to check if the cycle exist
	 * @return boolean if the cycle already exists
	 */
	public boolean checkIfCycleExist(String name) {
		if (name.isBlank()) {
			System.out.println("Error:the string is not valid");
			return true;
		}

		for (Event i : this.getEvents()) {
			if (i instanceof Cycle) {
				if (i.getTitle().equals(name)) {
					return true;
				}
			}
		}
		return false;
	}

	/**
	 * Method that creates a performance of an event
	 * 
	 * @param event that will contain the performance
	 * @param date  of the performance
	 * @return boolean if the operation has been done successfully
	 */
	public boolean createPerformance(Event event, LocalDateTime date) {
		if (event == null || date == null) {
			System.out.println("Error:event or date invalid");
			return false;
		}
		if (this.checkIfPerformanceExist(event, date)) {
			System.out.println("Error:the performance already exixts");
			return false;
		}
		return event.createPerformance(date, this.zones);
	}

	/**
	 * Method that checks if a performance exists
	 * 
	 * @param event that contains the performances to check
	 * @param date  of the performance to be checked
	 * @return boolean if the performance at that date already exists
	 */
	public boolean checkIfPerformanceExist(Event event, LocalDateTime date) {
		if (date == null || event == null) {
			System.out.println("Error:the date or the event is not valid");
			return true;
		}
		return event.checkIfPerformanceExist(date);
	}

	/**
	 * Method to postpone a performance to a new date
	 * 
	 * @param performance to modify the date
	 * @param newDate     to be established in the performance
	 * @return boolean if the performance at that date already exists
	 */
	public boolean postponePerformace(Performance performance, LocalDateTime newDate) {
		if (performance == null || newDate == null) {
			System.out.println("Error:performance or date invalid");
			return false;
		}
		if (newDate.isAfter(performance.getDate())) {
			performance.postponePerformance(newDate);
			return true;
		}
		return false;
	}

	/**
	 * Method to cancel/delete a performance
	 * 
	 * @param performance to be cancelled
	 */
	public void cancelPerformance(Performance performance) {
		if (performance == null) {
			System.out.println("Error:The performance doesn't exist");
			return;
		}
		performance.getEvent().cancelPerformance(performance);
		for (Statistic s : this.statistics) {
			if (s instanceof PerformanceStatistic) {
				if (((PerformanceStatistic) s).getPerformance().equals(performance)) {
					this.statistics.remove(s);
					break;
				}
			}
		}
	}

	/**
	 * Method to create a new cycle
	 * 
	 * @param title of the new cycle
	 * @return boolean if the operation has been done successfully
	 */
	public boolean createCycle(String title) {
		if (title.isBlank()) {
			System.out.println("Error:invalid title");
			return false;
		}
		if (this.checkIfCycleExist(title)) {
			System.out.println("Error:the cycle already exixts");
			return false;
		}
		this.events.add(new Cycle(title));
		return true;
	}

	/**
	 * Method that adds an event to a cycle
	 * 
	 * @param event to be added in the cycle
	 * @param cycle where the event will be added
	 */
	public void addEventToCycle(Event event, Cycle cycle) {
		if (event == null || cycle == null) {
			System.out.println("Error:The event or the cycle doesn't exist");
			return;
		}
		cycle.addEvent(event);
	}

	/**
	 * Method to create a cycle pass
	 * 
	 * @param name     of the cycle pass
	 * @param discount applied to the sum of the prices of all the events contained
	 *                 in a cycle
	 * @param zone     of the cycle pass
	 * @param cycle    related to the cycle pass
	 * @return boolean if the operation has been done successfully
	 */
	public boolean createCyclePass(String name, int discount, Zone zone, Cycle cycle) {
		if (name.isBlank()) {
			System.out.println("Error:invalid title");
			return false;
		}
		if (discount > 100 || discount < 0) {
			System.out.println("Error:Discount percentage invalid");
			return false;
		}
		if (zone == null || cycle == null) {
			System.out.println("Error:The zone or the cycle wasn't selected correctly");
			return false;
		}
		if (getPass(name) != null) {
			System.out.println("Error:Pass already exists");
			return false;
		}
		this.passes.add(new CyclePass(name, discount, zone, cycle));
		return true;
	}

	/**
	 * Method to get a pass given a name
	 * 
	 * @param passName of the pass
	 * @return the corresponding pass
	 */
	public Pass getPass(String passName) {
		if (passName.isBlank()) {
			System.out.println("Error: getPass wrong input");
			return null;
		}
		for (Pass pa : this.passes) {
			if (pa.getName().equals(passName)) {
				return pa;
			}
		}
		return null;
	}

	/**
	 * Method to create an annual pass
	 * 
	 * @param c    cutomer that wants to buy an annual pass
	 * @param zone of the annual pass
	 * @return boolean if the operation has been done successfully
	 */
	public boolean createAnnualPass(Customer c, Zone zone) {
		if (zone == null || c == null) {
			return false;
		}
		if (this.getAnnualPrice(zone) < 0) {
			System.out.println("Price not set for zone " + zone.getName());
			return false;
		}
		AnnualPass ap = new AnnualPass(this.getAnnualPrice(zone), zone);
		if (ap == null) {
			return false;
		}
		c.addPass(ap);
		return true;
	}

	/**
	 * Method to get the price of an annual pass in a zone
	 * 
	 * @param zone to check the price of the annual pass
	 * @return double with the price of tha annual pass
	 */
	public double getAnnualPrice(Zone zone) {
		for (Price pz : this.annualPassPrice) {
			if (pz.getZone().equals(zone)) {
				return pz.getPrice();
			}
		}
		System.out.println("There is no price for that zone");
		return -1;
	}

	/**
	 * Method to register in the app
	 * 
	 * @param username of the new user
	 * @param password of the new user
	 * @return boolean if the resgistration has been done successfully
	 */
	public boolean register(String username, String password) {
		if (username.isBlank() || password.isBlank()) {
			System.out.println("Error:Invalid username or password\n");
			return false;
		}
		for (RegisteredUser ru : this.users) {
			if (username.equals(ru.getUsername())) {
				System.out.println("ErrTr:here is another user with that username\n");
				return false;
			}
		}
		this.users.add(new Customer(username, password));
		return true;
	}

	/**
	 * Method to set the time to pay a ticket after booking
	 * 
	 * @param ttp new time to pay in hours
	 */
	public void setTTP(int ttp) {
		if (ttp < 0) {
			System.out.println("Error:Invalid ttp\n");
			return;
		}
		this.ttp = ttp;
	}

	/**
	 * Method to set the time to book the ticket while being in the waitlist
	 * 
	 * @param ttb new time to book in hours
	 */
	public void setTTB(int ttb) {
		if (ttb < 0) {
			System.out.println("Error:Invalid ttp\n");
			return;
		}
		this.ttb = ttb;
	}

	/**
	 * Method to get the time to pay
	 * 
	 * @return int with the time to pay in hours
	 */
	public int getTTP() {
		return this.ttp;
	}

	/**
	 * Method to get the time to book
	 * 
	 * @return int with the time to book in hours
	 */
	public int getTTB() {
		return this.ttb;
	}

	/**
	 * Method to get list of events o the theater
	 * 
	 * @return arraylist with all the events of the theater
	 */
	public ArrayList<Event> getEvents() {
		return this.events;
	}

	/**
	 * Method that allow a customer to book a ticket
	 * 
	 * @param c customer that wants to book the ticket
	 * @param t to be booked
	 */
	public void bookTicket(Customer c, Ticket t) {
		if (c == null || t == null) {
			System.out.println("Error:invalid customer or ticket\n");
			return;
		}
		if (LocalDateTime.now().isAfter(t.getPerformance().getDate().minusHours(ttb))) {
			System.out.println("You can't book now since you are past the last booking time : \n"
					+ t.getPerformance().getDate().minusHours(ttb));
			return;
		}
		t.setBookedTicket(new Booked(LocalDateTime.now().plusHours(this.ttp)));
		c.addTicket(t);

	}

	/**
	 * Method that checks if the booking of a customer for a ticket is out of time
	 * 
	 * @param c      customer that booked the ticket
	 * @param ticket that was booked
	 * @return boolean if the booking is still valid
	 */
	public boolean checkBooking(Customer c, Ticket ticket) {
		if (c == null || ticket == null) {
			System.out.println("Error:invalid customer or ticket\n");
			return false;
		}
		if (ticket.getBookedTicket().checkOutOfTime()) {
			cancelBooking(c, ticket);
			return false;
		}
		return true;
	}

	/**
	 * Method that allow a customer to cancel a booking
	 * 
	 * @param c      customer that wants to cancel the booking
	 * @param t that was booked
	 */
	public void cancelBooking(Customer c, Ticket t) {
		if (c == null || t == null) {
			System.out.println("Error: invalid customer or ticket\n");
			return;
		}
		c.removeTicket(t);
		t.setBookedTicket(null);
		t.freeTicket();
		t.getPerformance().cancelPerformanceTicket(t);
		t = null;
	}

	/**
	 * Method to purchase a ticket that was booked
	 * 
	 * @param c customer that booked a ticket
	 * @param t ticket that was booked
	 */
	public void purchaseBooked(Customer c, Ticket t) {
		if (c == null || t == null) {
			System.out.println("Error: invalid customer or ticket\n");
			return;
		}
		if (t.getBookedTicket().checkOutOfTime()) {
			System.out.println("You lost the reservation at " + t.getBookedTicket().getTTP());
			t.setBookedTicket(null);
			return;
		}
		c.removeTicket(t);
		t.setPurchased(true);
		t.setBookedTicket(null);
		c.addTicket(t);
	}

	/**
	 * Method that allow a customer to join a waitlist of a performace
	 * 
	 * @param customer    that wants to join the waitlist
	 * @param performance that that contains the waitlist
	 * 
	 * @return the result of trying to subscribe
	 */
	public boolean suscribeToWaitList(Customer customer, Performance performance) {
		if (customer == null || performance == null) {
			System.out.println("Error: invalid customer or performance\n");
			return false;
		}
		if (performance.checkIfFull()) {
			performance.getWaitList().subscribeToWaitList(customer);
			return true;
		} else {
			System.out.println("The performance is still not full");
			return false;
		}
	}

	/**
	 * Method that allow a customer to leave a waitlist of a performace
	 * 
	 * @param customer    that wants to leave the waitlist
	 * @param performance that that contains the waitlist
	 */
	public void unsuscribeOfWaitList(Customer customer, Performance performance) {
		if (customer == null || performance == null) {
			System.out.println("Error: invalid customer or performance\n");
			return;
		}
		performance.getWaitList().unsubscribeOfWaitList(customer);
	}

	/**
	 * Method that creates a standing zone
	 * 
	 * @param name            of the zone to be created
	 * @param maxPeople       that can contain the zone
	 * @param annualPassPrice price for that zone in the annual pass
	 * @return boolean if the operation has been done successfully
	 */
	public boolean createStandingZone(String name, int maxPeople, double annualPassPrice) {

		if (name.isBlank()) {
			System.out.println("Error:invalid name");
			return false;
		}
		if (maxPeople < 0) {
			System.out.println("Error: e doevalid number of people\n");
			return false;
		}
		if (checkIfZoneExist(name) == true) {
			System.out.println("Error:name of that zone already taken\n");
			return false;
		}

		StandingZone sz = new StandingZone(name, maxPeople);
		if (sz == null) {
			return false;
		}
		this.statistics.add(new ZoneStatistic(name, sz));
		this.zones.add(sz);
		this.annualPassPrice.add(new Price(sz, annualPassPrice));
		return true;
	}

	/**
	 * Method that creates a standing subzone
	 * 
	 * @param name            of the zone to be created
	 * @param maxPeople       that can contain the zone
	 * @param parent          name of the parent zone
	 * @param annualPassPrice price for that zone in the annual pass
	 * @return boolean if the operation has been done successfully
	 */
	public boolean createStandingZone(String name, int maxPeople, String parent, double annualPassPrice) {
		if (maxPeople < 0) {
			System.out.println("Error:invalid number of people\n");
			return false;
		}
		if (name.isBlank() || parent.isBlank()) {
			System.out.println("Error:invalid name of the zone or  of the parent zone\n");
			return false;
		}
		if (checkIfZoneExist(name) == true) {
			System.out.println("Error:name of that zone already taken\n");
			return false;
		}
		FragmentedZone sz = ((FragmentedZone) this.getZone(parent));
		if (sz == null) {
			System.out.println("Error:unable to find the parent zone\n");
			return false;
		}
		StandingZone sz1 = new StandingZone(name, maxPeople);
		if (sz == null) {
			return false;
		}
		sz.addSubzone(sz1);
		sz1.setDad(sz);
		this.statistics.add(new ZoneStatistic(name, sz1));
		this.annualPassPrice.add(new Price(sz1, annualPassPrice));
		return true;
	}

	/**
	 * Method that creates a sitting zone
	 * 
	 * @param name            of the zone to be created
	 * @param nRows           number of rows of the zone
	 * @param nColumns        number of columns of the zone
	 * @param annualPassPrice price for that zone in the annual pass
	 * @return boolean if the operation has been done successfully
	 */
	public boolean createSittingZone(String name, int nRows, int nColumns, double annualPassPrice) {
		if (name.isBlank()) {
			System.out.println("Error:invalid name of the zone\n");
			return false;
		}
		if (nRows < 0 || nColumns < 0) {
			System.out.println("Error:invalid number of rows or columns\n");
			return false;
		}
		if (checkIfZoneExist(name) == true) {
			System.out.println("Error:name of that zone already taken\n");
			return false;
		}
		SittingZone sz = new SittingZone(name, nRows, nColumns);
		if (sz == null) {
			return false;
		}
		this.zones.add(sz);
		this.statistics.add(new ZoneStatistic(name, sz));
		this.annualPassPrice.add(new Price(sz, annualPassPrice));
		return true;
	}

	/**
	 * Method that creates a sitting zone
	 * 
	 * @param name            of the zone to be created
	 * @param nRows           number of rows of the zone
	 * @param nColumns        number of columns of the zone
	 * @param parent          string with name of the parent zone
<<<<<<< HEAD
	 * @param AnnualPassPrice price for that zone in the annual pass
=======
	 * @param annualPassPrice price for that zone in the annual pass
>>>>>>> 1cd9b5ca3eae2f21b66106514195f08a9f18320b
	 * @return boolean if the operation has been done successfully
	 */
	public boolean createSittingZone(String name, int nRows, int nColumns, String parent, double AnnualPassPrice) {
		if (nRows < 0 || nColumns < 0) {
			System.out.println("Error:invalid number of rows or columns\n");
			return false;
		}
		if (name.isBlank() || parent.isBlank()) {
			System.out.println("Error:invalid zone name or parent zone name\n");
			return false;
		}
		if (checkIfZoneExist(name) == true) {
			System.out.println("Error:name of that zone already taken\n");
			return false;
		}

		FragmentedZone sz = ((FragmentedZone) this.getZone(parent));

		if (sz == null) {
			System.out.println("Error:unable to find the parent zone\n");
			return false;
		}
		SittingZone sz1 = new SittingZone(name, nRows, nColumns);

		if (sz1 == null) {
			return false;
		}
		sz.addSubzone(sz1);
		sz1.setDad(sz);
		this.statistics.add(new ZoneStatistic(name, sz1));
		this.annualPassPrice.add(new Price(sz1, AnnualPassPrice));
		return true;
	}

	/**
	 * Method that creates a fragmented zone
	 *
	 * @param name of the zone to be created
	 * @return boolean if the operation has been done successfully
	 */
	public boolean createFragmentedZone(String name) {
		if (name.isBlank()) {
			System.out.println("Error:invalid zone name\n");
			return false;
		}
		if (checkIfZoneExist(name) == true) {
			System.out.println("Error:name of that zone already taken\n");
			return false;
		}
		FragmentedZone fz = new FragmentedZone(name);
		if (fz == null) {
			return false;
		}
		this.zones.add(fz);
		this.statistics.add(new ZoneStatistic(name, fz));
		return true;
	}

	/**
	 * Method that creates a fragmented subzone
	 *
	 * @param name   of the zone to be created
	 * @param parent name of the parent zone
	 * @return boolean if the operation has been done successfully
	 */
	public boolean createFragmentedZone(String name, String parent) {
		if (name.isBlank() || parent.isBlank()) {
			System.out.println("Error:invalid zone name or parent zone name\n");
			return false;
		}
		if (checkIfZoneExist(name) == true) {
			System.out.println("Error:name of that zone already taken\n");
			return false;
		}
		for (Zone z : this.zones) {
			if (z.getName().equals(parent)) {
				FragmentedZone sz = (FragmentedZone) z;
				if (sz == null) {
					return false;
				}
				FragmentedZone fz = new FragmentedZone(name);
				if (fz == null) {
					return false;
				}
				sz.addSubzone(fz);
				fz.setDad(sz);
				this.statistics.add(new ZoneStatistic(name, fz));
			}
		}
		return true;
	}

	/**
	 * Method that deletes a zone
	 *
	 * @param zone to be deleted
	 */
	public void deleteZone(Zone zone) {
		if (zone == null) {
			System.out.println("Error:The zone doesn't exist\n");
			return;
		}
		for (Statistic s : this.statistics) {
			if (s instanceof ZoneStatistic) {
				if (((ZoneStatistic) s).getZone().equals(zone)) {
					this.statistics.remove(s);
					break;
				}
			}
		}

		for (Zone z : this.zones) {
			if (zone.getName().equals(z.getName())) {
				this.zones.remove(zone);
				return;
			} else if (z instanceof FragmentedZone) {
				((FragmentedZone) z).removeSubZone(zone);
			}
		}

	}

	/**
	 * Method to get all the fragmented zones
	 *
	 * @return list with all the fragmented zones
	 */
	public ArrayList<Zone> getFragmentedZones() {
		ArrayList<Zone> aux = new ArrayList<Zone>();
		for (Zone z : this.zones) {
			if (z instanceof FragmentedZone) {
				FragmentedZone fz = (FragmentedZone) z;
				aux.add(fz);
				aux.addAll(fz.getFragmentedsubZones());
			}
		}
		return aux;
	}

	/**
	 * Method that checks if a zone exists
	 *
	 * @param name of the zone to be checked
	 * @return boolean if the zone exists
	 */
	public boolean checkIfZoneExist(String name) {
		if (name.isBlank()) {
			System.out.println("Error:invalid zone name\n");
			return false;
		}
		if (this.getZone(name) != null) {
			return true;
		}
		return false;
	}

	/**
	 * Method that starts a maintenance in a seat
	 *
	 * @param zone    String with the name of the zone
	 * @param row     the seat row
	 * @param column  the seat column
	 * @param dateEnd with the end of the maintenance
	 * @param notes   about the maintenance
	 * 
	 * @return the state of maintenance of the seat
	 */
	public boolean mantainSeat(String zone, int row, int column, LocalDate dateEnd, String notes) {
		SittingZone sz = (SittingZone) this.getZone(zone);
		if (sz.getNRows() < (row) || sz.getNRows() < (column) || this.checkIfZoneExist(zone) || dateEnd == null) {
			return false;
		}
		for (Event e : this.getEvents()) {
			if (!(e instanceof Cycle)) {
				for (Performance p : e.getPerformances()) {
					LocalDate pDate = LocalDate.of(p.getDate().getYear(), p.getDate().getMonth(),
							p.getDate().getDayOfMonth());
					if (pDate.isBefore(dateEnd)) {
						System.out.println("Seat [" + row + column + "] del eventofrom event " + e.getTitle()
								+ " in performance " + p.getDate());
						((SittingZone) p.getZone(zone)).getSeat(row, column).maintainSeat(dateEnd, notes);
					}
				}
			}
		}

		((SittingZone) this.getZone(zone)).getSeat(row, column).maintainSeat(dateEnd, notes);
		return true;

	}

	/**
	 * Method that updates the statistics of a performance
	 *
	 * @param eventName name of the event that contains the performance
	 * @param date      of the performance that we want to update the statistics
	 * @param zoneName  name of the zone that we want to check
	 */
	public void updatePerformanceZoneStatistic(String eventName, LocalDateTime date, String zoneName) {
		if (eventName.isBlank() || date == null || zoneName.isBlank()) {
			System.out.println("Error:invalid date, event or zone\n");
			return;
		}
		Event event = getEvent(eventName);
		Zone zone = getZone(zoneName);
		Performance performance = event.getPerformance(date);

		for (Statistic s : this.statistics) {
			if (s.getName().equals(zone.getName())) {
				ZoneStatistic zs = (ZoneStatistic) s;
				zs.updateStatisticsFromPerformance(event, performance, zone);
				break;
			}
		}

	}

	/**
	 * Method to get the statistic of a zone
	 *
	 * @param zoneName name of the zone that we want to get the statistics
	 * @return zonestatistic statistic of the corresponding zone
	 */
	public ZoneStatistic getZoneStatistic(String zoneName) {
		if (zoneName.isBlank()) {
			System.out.println("Error: Invalid zone name");
		}
		for (Statistic s : this.statistics) {
			if (s instanceof ZoneStatistic) {
				if (s.getName().equals(zoneName)) {
					return (ZoneStatistic) s;
				}
			}
		}
		return null;
	}

	/**
	 * returns all the zones of the theater where you can buy a ticket
	 * 
	 * @return array of zones
	 */
	public ArrayList<Zone> getUsableZones() {
		ArrayList<Zone> zs = new ArrayList<>();
		for (Zone zone : this.zones) {
			if (zone instanceof FragmentedZone) {
				for (Zone sz : ((FragmentedZone) zone).getUsableSubZones()) {
					zs.add(sz);
				}
			} else {
				zs.add(zone);
			}

		}
		return zs;
	}

	/**
	 * Method to get the statistic of an event
	 *
	 * @param eventName name of the event that we want to get the statistics of
	 * @return eventstatistic statistics of the event with the given name
	 */
	public EventStatistic getEventStatistic(String eventName) {
		if (eventName.isBlank()) {
			System.out.println("Error: Invalid event name");
		}
		for (Statistic s : this.statistics) {
			if (s instanceof EventStatistic) {
				if (s.getName().equals(eventName)) {
					return (EventStatistic) s;
				}
			}
		}
		return null;
	}

	/**
	 * Method to get the statistic of a performance
	 *
	 * @param eventName name of the event that contains the performance that we want
	 *                  to get the statistics of
	 * @param date      of the performance that we want to get the statistics
	 * @return performancestatistic statistics of the performance with the given
	 *         date
	 */
	public PerformanceStatistic getPerformanceStatistic(String eventName, LocalDateTime date) {
		if (date == null) {
			System.out.println("Error: Invalid date");
		}
		Event event = getEvent(eventName);
		Performance performance = event.getPerformance(date);
		for (Statistic s : this.statistics) {
			if (s instanceof PerformanceStatistic) {
				if ((((PerformanceStatistic) s).getPerformance().getEvent().getTitle().equals(event.getTitle()))
						&& ((PerformanceStatistic) s).getPerformance().getDate().equals(performance.getDate())) {
					return (PerformanceStatistic) s;
				}
			}
		}
		return null;
	}

	/**
	 * Method that updates the statistics of an event in a zone
	 *
	 * @param eventName name of the event that we want to update the statistics of
	 * @param zoneName  name of the zone where we want to update the statistics
	 */
	public void updateEventZoneStatistic(String eventName, String zoneName) {
		if (eventName.isBlank() || zoneName.isBlank()) {
			System.out.println("Error:invalid event or zone\n");
			return;
		}
		Event event = getEvent(eventName);
		Zone zone = getZone(zoneName);
		if (event instanceof Cycle) {
			System.out.println("Cycles are not valid");
			return;
		}
		ZoneStatistic zs = null;
		for (Statistic s : this.statistics) {
			if (s.getName().equals(zone.getName())) {
				zs = (ZoneStatistic) s;
				break;
			}
		}
		zs.updateStatisticsFromEvent(event, zone);
	}

	/**
	 * Method that updates the statistics of a zone
	 *
	 * @param zoneName name of the zone where we want to update the statistics
	 */
	public void updateZoneStatistic(String zoneName) {
		if (zoneName.isBlank()) {
			System.out.println("Error:invalid zone\n");
			return;
		}
		Zone zone = getZone(zoneName);

		ZoneStatistic zs = null;
		for (Statistic s : this.statistics) {
			if (s.getName().equals(zone.getName())) {
				zs = (ZoneStatistic) s;
				break;
			}
		}

		zs.updateStatistics(this.events, zone);
	}

	/**
	 * Method that updates the statistics of an event
	 *
	 * @param eventName name of the event that we want to update the statistics
	 */
	public void updateEventStatistic(String eventName) {
		EventStatistic es = null;
		Event event = getEvent(eventName);
		if (event == null) {
			System.out.println("Error:invalid event\n");
			return;
		}
		for (Statistic s : this.statistics) {
			if (s.getName().equals(event.getTitle())) {
				es = (EventStatistic) s;
				break;
			}
		}
		es.updateStatistics(event);
	}

	/**
	 * Method that updates the statistics of a performance
	 *
	 * @param eventName name of the event that contains the performance that we want
	 *                  to update
	 * @param date      of the performance that we want to update the statistics
	 */
	public void updatePerformanceStatistic(String eventName, LocalDateTime date) {
		if (eventName.isBlank() || date == null) {
			System.out.println("Error:invalid event or date\n");
			return;
		}
		Event event = getEvent(eventName);

		Performance performance = event.getPerformance(date);
		PerformanceStatistic ps = null;
		boolean flag = false;

		for (Statistic s : this.statistics) {
			if ((s instanceof PerformanceStatistic)) {
				if ((((PerformanceStatistic) s).getPerformance().getEvent().getTitle().equals(event.getTitle()))
						&& ((PerformanceStatistic) s).getPerformance().getDate().equals(performance.getDate())) {

					flag = true;
					ps = (PerformanceStatistic) s;
				}
			}

		}
		if (flag == false)

		{
			ps = new PerformanceStatistic(event.getTitle() + date, performance);
			this.statistics.add(ps);
		}

		ps.updateStatistics(event, performance);
	}

	/**
	 * Method to set the occupancy percentage in the theater
	 *
	 * @param o int with the new occupancy percentage
	 */
	public void setOccupancy(int o) {
		if (o < 0 || o > 100) {
			System.out.println("Error:invalid occupancy\n");
			return;
		}

		for (Event e : this.getEvents()) {
			if (e instanceof Cycle) {
			} else {
				for (Performance p : e.getPerformances()) {
					for (Zone z : p.getZones()) {
						z.setOccupancy(o);
					}
				}
			}
		}
		for (Zone z : this.zones) {
			z.setOccupancy(o);
		}
	}

	/**
	 * Method to set the price of an event in a zone
	 *
	 * @param eventName name of the event where we want to set the price
	 * @param zoneName  name of the zone where we want to apply the price
	 * @param price     to be established in the zone
	 */
	public void setPrice(String eventName, String zoneName, double price) {
		;
		if (eventName.isBlank() || zoneName.isBlank()) {
			System.out.println("Error:the event or the zone doens't exist\n");
			return;
		}
		if (price < 0) {
			System.out.println("Error:invalid price\n");
			return;
		}
		Event e = getEvent(eventName);
		Zone zone = getZone(zoneName);
		e.setPrice(zone, price);
	}

	/**
	 * Checks if card number is valid
	 * 
	 * @param cardNumber card number
	 * @return true if valid else false
	 */
	public boolean checkCard(String cardNumber) {
		if (cardNumber.isBlank()) {
			System.out.println("Error:Invalid credit card number\n");
			return false;
		}
		return TeleChargeAndPaySystem.isValidCardNumber(cardNumber);
	}

	/**
	 * return user from user name
	 * 
	 * @param userName user's name
	 * @return requested RegisterUser object
	 */
	public RegisteredUser getCustomer(String userName) {
		for (RegisteredUser c : this.users) {
			if (c.getUsername().equals(userName)) {
				return c;
			}
		}
		System.out.println("The customer is not registered\n");
		return null;
	}

	/**
	*  A method to get all the users
	* @return arraylist with all the users
	*/
	public ArrayList<RegisteredUser> getUsers() {
		return this.users;
	}

	/**
	 * A method to update all the booking status
<<<<<<< HEAD
	 * @param c customer
	 * @return number of canceled tickets
	 */
	public int updateBookings(Customer c) {
		int n = 0;

				for (Ticket t : c.getTickets()) {
					if (checkBooking(c, t) == false) {
						n ++;
					}
				}
		return n;
=======
	 * 
	 * @return arraylist of customers with canceled tickets
	 */
	public ArrayList<Customer> updateBookings() {
		ArrayList<Customer> customers = new ArrayList<>();
		for (RegisteredUser u : this.users) {
			if (u instanceof Customer) {
				Customer c = (Customer) u;
				for (Ticket t : c.getTickets()) {
					if (checkBooking(c, t) == false) {
						customers.add(c);
					}

				}
			}

		}
		return customers;
>>>>>>> 1cd9b5ca3eae2f21b66106514195f08a9f18320b
	}

	/**
	 * return Event pointer from event name
	 * 
	 * @param eventName event's name
	 * @return poiinter to requested event
	 */
	public Event getEvent(String eventName) {
		for (Event e : this.events) {
			if (e.getTitle().equals(eventName)) {
				return e;
			}
		}
		System.out.println("The Event is not existent\n");
		return null;
	}

	/**
	 * return Zone pointer from zone name
	 * 
	 * @param zoneName zone's name
	 * @return pointer to requested zone
	 */
	public Zone getZone(String zoneName) {
		if (zoneName == null) {
			System.out.println("Error: getZone method in Performance recieves a null zone\n");
			return null;
		}
		for (Zone zone : this.zones) {
			if (zone instanceof FragmentedZone) {
				if (((FragmentedZone) zone).getSubZone(zoneName) != null) {
					return ((FragmentedZone) zone).getSubZone(zoneName);
				}
			}
			if (zone.getName() == zoneName) {
				return zone;
			}
		}
		return null;
	}

	/**
	 * Method to get all the passes created in the app
	 * 
	 * @return arraylist with all the passes
	 */
	public ArrayList<Pass> getPasses() {
		return this.passes;
	}

	/**
	 * Method that opens object output stream
	 * 
	 * @param name string with file name
	 * @return object output stream
	 * @throws FileNotFoundException if the file doesnt exist
	 * @throws IOException if the file cant be read
	 */
	public ObjectOutputStream openBinOut(String name) throws FileNotFoundException, IOException {
		ObjectOutputStream out;
		out = new ObjectOutputStream(new FileOutputStream("./obj/" + name + ".objectData"));
		return out;
	}

	/**
	 * Method that close object output stream
	 * 
	 * @param out object output stream
	 * @throws FileNotFoundException exception
	 * @throws IOException           exception
	 */
	public void closeBinOut(ObjectOutputStream out) throws FileNotFoundException, IOException {
		out.close();
	}

	/**
	 * Method that save objects into object files
	 * 
	 * @throws IOException exception
	 */
	public void save() throws IOException {
		ObjectOutputStream out;

		out = openBinOut("app");
		saveApp(out);
		closeBinOut(out);

		out = openBinOut("tts");

		closeBinOut(out);

		out = openBinOut("zones");
		saveZones(out, this.zones);
		closeBinOut(out);

		out = openBinOut("events");
		saveEvents(out);
		closeBinOut(out);

		out = openBinOut("annualPassPrices");
		saveAnnualPassPrices(out);
		closeBinOut(out);

		out = openBinOut("users");
		saveUsers(out);
		closeBinOut(out);

		out = openBinOut("passes");
		savePasses(out);
		closeBinOut(out);

		out = openBinOut("statistics");
		saveStatistics(out);
		closeBinOut(out);

		out = openBinOut("performances");
		savePerformances(out);
		closeBinOut(out);

		out = openBinOut("prices");
		savePrices(out);
		closeBinOut(out);

		out = openBinOut("tickets");
		saveTickets(out);
		closeBinOut(out);

		out = openBinOut("books");
		saveBooks(out);
		closeBinOut(out);

		out = openBinOut("waitlists");
		saveWaitLists(out);
		closeBinOut(out);

		out = openBinOut("seats");
		saveSeats(out, this.zones);
		closeBinOut(out);

	}

	/**
	 * Method that save TheaterApp object
	 *
	 * @param out object output stream
	 * @throws IOException exception
	 */
	public void saveApp(ObjectOutputStream out) throws IOException {
		out.writeObject(this);
	}

	/**
	 * Method that save the Zone objects
	 *
	 * @param out   object output stream
	 * @param zones array to search
	 * @throws IOException exception
	 */
	public void saveZones(ObjectOutputStream out, List<Zone> zones) throws IOException {

		for (Zone z : zones) {
			if (z instanceof FragmentedZone) {
				saveZones(out, ((FragmentedZone) z).getSubZones());
			}
			out.writeObject(z);

		}
	}

	/**
	 * Method that save Price objects from annual pass
	 * 
	 * @param out object output stream
	 * @throws IOException exception
	 */
	public void saveAnnualPassPrices(ObjectOutputStream out) throws IOException {
		for (Price p : this.annualPassPrice) {
			out.writeObject(p);
		}
	}

	/**
	 * Method that save Event objects
	 * 
	 * @param out object output stream
	 * @throws IOException exception
	 */
	public void saveEvents(ObjectOutputStream out) throws IOException {
		for (Event e : this.events) {
			out.writeObject(e);
		}
	}

	/**
	 * Method that save User objects
	 * 
	 * @param out object output stream
	 * @throws IOException exception
	 */
	public void saveUsers(ObjectOutputStream out) throws IOException {
		for (RegisteredUser u : this.users) {
			out.writeObject(u);
		}
	}

	/**
	 * Method that save Pass objects
	 * 
	 * @param out object output stream
	 * @throws IOException exception
	 */
	public void savePasses(ObjectOutputStream out) throws IOException {
		for (Pass p : this.passes) {
			out.writeObject(p);
		}
	}

	/**
	 * Method that save Statistic objects
	 * 
	 * @param out object output stream
	 * @throws IOException exception
	 */
	public void saveStatistics(ObjectOutputStream out) throws IOException {
		for (Statistic s : this.statistics) {
			out.writeObject(s);
		}
	}

	/**
	 * Method that save Performance objects
	 * 
	 * @param out object output stream
	 * @throws IOException exception
	 */
	public void savePerformances(ObjectOutputStream out) throws IOException {
		for (Event e : this.events) {
			if (!(e instanceof Cycle)) {
				for (Performance p : e.getPerformances()) {
					out.writeObject(p);
				}
			}
		}
	}

	/**
	 * Method that save Price objects
	 * 
	 * @param out object output stream
	 * @throws IOException exception
	 */
	public void savePrices(ObjectOutputStream out) throws IOException {
		for (Event e : this.events) {
			if (!(e instanceof Cycle)) {
				for (Price p : e.getPrices()) {
					out.writeObject(p);
				}
			}
		}
	}

	/**
	 * Method that save Ticket objects
	 * 
	 * @param out object output stream
	 * @throws IOException exception
	 */
	public void saveTickets(ObjectOutputStream out) throws IOException {
		Customer c;
		for (RegisteredUser u : this.users) {
			if (u instanceof Customer) {
				c = (Customer) u;
				for (Ticket t : c.getTickets()) {
					out.writeObject(t);
				}
			}
		}
	}

	/**
	 * Method that save Booked objects
	 * 
	 * @param out object output stream
	 * @throws IOException exception
	 */
	public void saveBooks(ObjectOutputStream out) throws IOException {
		Customer c;
		for (RegisteredUser u : this.users) {
			if (u instanceof Customer) {
				c = (Customer) u;
				for (Ticket t : c.getTickets()) {
					if (t.getBookedTicket() != null) {
						out.writeObject(t.getBookedTicket());
					}
				}
			}
		}
	}

	/**
	 * Method that save WaitList objects
	 * 
	 * @param out object output stream
	 * @throws IOException exception
	 */
	public void saveWaitLists(ObjectOutputStream out) throws IOException {
		for (Event e : this.events) {
			if (!(e instanceof Cycle)) {
				for (Performance p : e.getPerformances()) {
					out.writeObject(p.getWaitList());
				}
			}
		}
	}

	/**
	 * Method that save Seat objects
	 * 
	 * @param out   object output stream
	 * @param zones zones to be checked for seats
	 * @throws IOException exception
	 */
	public void saveSeats(ObjectOutputStream out, List<Zone> zones) throws IOException {
		Seat[][] matrix;

		for (Zone z : zones) {

			if (z instanceof FragmentedZone) {
				saveSeats(out, ((FragmentedZone) z).getSubZones());
			}
			if (z instanceof SittingZone) {

				matrix = ((SittingZone) z).getMatrix();
				for (int i = 0; i < ((SittingZone) z).getNRows(); i++) {
					for (int j = 0; j < ((SittingZone) z).getNColumns(); j++) {
						out.writeObject(matrix[i][j]);
					}
				}
			}

		}
	}

	/**
	 * Method that opens Object input stream
	 * 
	 * @param name file name
	 * @throws FileNotFoundException exception
	 * @throws IOException           exception
	 * @return object input stream
	 */
	public ObjectInputStream openBinIn(String name) throws FileNotFoundException, IOException {
		ObjectInputStream in = new ObjectInputStream(new FileInputStream("./obj/" + name + ".objectData"));
		return in;
	}

	/**
	 * Method that closes Object input stream
	 * 
	 * @param in object input stream
	 * @throws FileNotFoundException exception
	 * @throws IOException           exception
	 */
	public void closeBinIn(ObjectInputStream in) throws FileNotFoundException, IOException {
		in.close();
	}

	/**
	 * Method that loads all the saved object files as objects
	 * 
	 * @throws IOException            exception
	 * @throws ClassNotFoundException exception
	 */
	public void load() throws IOException, ClassNotFoundException {
		ObjectInputStream in;
		TheaterApp app;

		in = openBinIn("zones");
		loadZones(in);
		closeBinIn(in);

		in = openBinIn("events");
		loadEvents(in);
		closeBinIn(in);

		in = openBinIn("annualPassPrices");
		loadAnnualPassPrices(in);
		closeBinIn(in);

		in = openBinIn("users");
		loadUsers(in);
		closeBinIn(in);

		in = openBinIn("passes");
		loadPasses(in);
		closeBinIn(in);

		in = openBinIn("statistics");
		loadStatistics(in);
		closeBinIn(in);

		in = openBinIn("performances");
		loadPerformances(in);
		closeBinIn(in);

		in = openBinIn("prices");
		loadPrices(in);
		closeBinIn(in);

		in = openBinIn("tickets");
		loadTickets(in);
		closeBinIn(in);

		in = openBinIn("books");
		loadBooks(in);
		closeBinIn(in);

		in = openBinIn("waitlists");
		loadWaitList(in);
		closeBinIn(in);

		in = openBinIn("seats");
		loadSeats(in);
		closeBinIn(in);

	}

	/**
	 * Method that loads Zone objects
	 *
	 * @param in object input stream
	 * @throws ClassNotFoundException if the file doesnt exist
	 * @throws IOException if the file cant be read
	 */
	public void loadZones(ObjectInputStream in) throws ClassNotFoundException, IOException {
		try {
			Object object = in.readObject();
			Zone zone;

			while (object != null) {
				zone = (Zone) object;
				object = in.readObject();
			}
		} catch (EOFException e) {
			return;
		}
	}

	/**
	 * Method that load Event objects
	 * 
	 * @param in object input stream
	 * @throws ClassNotFoundException exception
	 * @throws IOException            exception
	 */
	public void loadEvents(ObjectInputStream in) throws ClassNotFoundException, IOException {
		try {
			Object object = in.readObject();
			Event e;

			while (object != null) {
				e = (Event) object;
				// this.events.add(e);
				object = in.readObject();
			}
		} catch (EOFException en) {
			return;
		}
	}

	/**
	 * Method that load AnnualPass Price objects
	 * 
	 * @param in object input stream
	 * @throws ClassNotFoundException exception
	 * @throws IOException            exception
	 */
	public void loadAnnualPassPrices(ObjectInputStream in) throws ClassNotFoundException, IOException {
		try {
			Object object = in.readObject();
			Price p;

			while (object != null) {
				p = (Price) object;
				// this.annualPassPrice.add(p);
				object = in.readObject();
			}
		} catch (EOFException e) {
			return;
		}
	}

	/**
	 * Method that load User objects
	 * 
	 * @param in object input stream
	 * @throws ClassNotFoundException exception
	 * @throws IOException            exception
	 */
	public void loadUsers(ObjectInputStream in) throws ClassNotFoundException, IOException {
		try {
			Object object = in.readObject();
			RegisteredUser u;

			while (object != null) {
				u = (RegisteredUser) object;
				// his.users.add(u);
				object = in.readObject();
			}
		} catch (EOFException e) {
			return;
		}
	}

	/**
	 * Method that load passes objects
	 * 
	 * @param in object input stream
	 * @throws ClassNotFoundException exception
	 * @throws IOException            exception
	 */
	public void loadPasses(ObjectInputStream in) throws ClassNotFoundException, IOException {
		try {
			Object object = in.readObject();
			Pass p;

			while (object != null) {
				p = (Pass) object;
				// this.passes.add();
				object = in.readObject();
			}
		} catch (EOFException e) {
			return;
		}
	}

	/**
	 * Method that load statistics objects
	 * 
	 * @param in object input stream
	 * @throws ClassNotFoundException exception
	 * @throws IOException            exception
	 */
	public void loadStatistics(ObjectInputStream in) throws ClassNotFoundException, IOException {
		Object object = in.readObject();
		Statistic s;
		try {
			while (object != null) {
				s = (Statistic) object;
				// this.statistics.add(s);
				object = in.readObject();
			}
		} catch (EOFException e) {
			return;
		}
	}

	/**
	 * Method that load performance objects
	 * 
	 * @param in object input stream
	 * @throws ClassNotFoundException exception
	 * @throws IOException            exception
	 */
	public void loadPerformances(ObjectInputStream in) throws ClassNotFoundException, IOException {
		try {
			Object object = in.readObject();
			Performance p;

			while (object != null) {
				p = (Performance) object;
				object = in.readObject();
			}
		} catch (EOFException e) {
			return;
		}

	}

	/**
	 * Method that load prices objects
	 * 
	 * @param in object input stream
	 * @throws ClassNotFoundException exception
	 * @throws IOException            exception
	 */
	public void loadPrices(ObjectInputStream in) throws ClassNotFoundException, IOException {
		try {
			Object object = in.readObject();
			Price p;

			while (object != null) {
				p = (Price) object;

				object = in.readObject();
			}
		} catch (EOFException e) {
			return;
		}

	}

	/**
	 * Method that load ticket objects
	 * 
	 * @param in object input stream
	 * @throws ClassNotFoundException exception
	 * @throws IOException            exception
	 */
	public void loadTickets(ObjectInputStream in) throws ClassNotFoundException, IOException {
		try {
			Object object = in.readObject();
			Ticket t;

			while (object != null) {
				t = (Ticket) object;

				object = in.readObject();
			}
		} catch (EOFException e) {
			return;
		}
	}

	/**
	 * Method that load books objects
	 * 
	 * @param in object input stream
	 * @throws ClassNotFoundException exception
	 * @throws IOException            exception
	 */
	public void loadBooks(ObjectInputStream in) throws ClassNotFoundException, IOException {
		try {
			Object object = in.readObject();
			Booked b;

			while (object != null) {
				b = (Booked) object;

				object = in.readObject();
			}
		} catch (EOFException e) {
			return;
		}
	}

	/**
	 * Method that load WaitList objects
	 * 
	 * @param in object input stream
	 * @throws ClassNotFoundException exception
	 * @throws IOException            exception
	 */
	public void loadWaitList(ObjectInputStream in) throws ClassNotFoundException, IOException {
		try {
			Object object = in.readObject();
			WaitList w;

			while (object != null) {
				w = (WaitList) object;

				object = in.readObject();
			}
		} catch (EOFException e) {
			return;
		}
	}

	/**
	 * Method that load Seat objects
	 * 
	 * @param in object input stream
	 * @throws ClassNotFoundException exception
	 * @throws IOException            exception
	 */
	public void loadSeats(ObjectInputStream in) throws ClassNotFoundException, IOException {
		try {
			Object object = in.readObject();
			Seat s;

			while (object != null) {
				s = (Seat) object;

				object = in.readObject();
			}
		} catch (EOFException e) {
			return;
		}
	}

	/**
	 * Method that returns requested zone from
	 * 
	 * @param p     performance 
	 * @param zoneName zone name
	 * @return requested Zone
	 */
	public Zone getPerformanceZone(Performance p, String zoneName) {
		return p.getZone(zoneName);
	}

	/**
	 * Method that returns a performance given the name of an event and a date
	 * 
	 * @param event string with the name of the event
	 * @param date  of he performance
	 * @return performance requested
	 */
	public Performance getPerformance(String event, LocalDateTime date) {
		for (Performance p : this.getEvent(event).getPerformances()) {
			if (p.getDate().equals(date)) {
				return p;
			}
		}
		return null;
	}

	/**
	 * Returns a valid pass for the customer to pay with if there is one
	 * 
	 * @param customerName customer name
	 * @param eventName    event to go with the pass
	 * @param zoneName     zone of the pass
	 * @return pass valid for the event
	 */
	public Pass getValidPass(String customerName, String eventName, String zoneName) {
		Pass pass = null;
		for (Pass p : ((Customer) getCustomer(customerName)).getPasses()) {
			if (!(p.getIfHasAlreadyAttended(getEvent(eventName)))) {
				if (p.getZone().equals(getZone(zoneName))) {
					if (p instanceof AnnualPass) {
						return p;
					} else if (((CyclePass) p).getCanGoToList().contains(getEvent(eventName))) {
						return p;
					}
				}
			}
		}
		return null;
	}

	/**
	 * Returns a valid pass for the customer to pay with if there is one
	 * 
	 * @param customerName customer name
	 * @param eventName    event to go with the pass
	 * @param zoneName     zone of the pass
	 * @return pass valid for the event
	 */
	public ArrayList<Pass> getValidPasses(String customerName, String eventName, String zoneName) {
		ArrayList<Pass> passes = new ArrayList<>();
		if (((Customer) getCustomer(customerName)).getAnnualPass() != null) {
			passes.add(((Customer) getCustomer(customerName)).getAnnualPass());
		}
		for (Pass p : ((Customer) getCustomer(customerName)).getPasses()) {
			if (!(p.getIfHasAlreadyAttended(getEvent(eventName)))) {
				if (p.getZone().equals(getZone(zoneName))) {
					if (!(p instanceof AnnualPass)) {
						if (((CyclePass) p).getCanGoToList().contains(getEvent(eventName))) {
							passes.add(p);
						}
					}
				}
			}
		}
		return passes;
	}

	/**
<<<<<<< HEAD
	 * Method to get all the zones of the theater
	 * 
	 * @return Array with all the zones
=======
	 * Method to initialize all the prices of an event
	 * 
	 * @param e event to initialize the prices
>>>>>>> 1cd9b5ca3eae2f21b66106514195f08a9f18320b
	 */
	public ArrayList<Zone> getAllZones() {
		ArrayList<Zone> zones = new ArrayList<>();
		for (Zone z : this.zones) {
			if (z instanceof FragmentedZone) {
				zones.addAll(getZonesFragmented(z));
			} else {
				zones.add(z);
			}
		}
		return zones;
	}

	/**
	 * Method to initialize the prices of a fragmented zone
	 * 
<<<<<<< HEAD
	 * @param zone where you want to initialize the Prices
	 * 
	 * @return an array with the zones inside that zone 
=======
	 * @param e    event to initialize the price
	 * @param zone where you want to initialize the Prices
>>>>>>> 1cd9b5ca3eae2f21b66106514195f08a9f18320b
	 */
	public ArrayList<Zone> getZonesFragmented(Zone zone) {
		if (zone == null) {
			System.out.println("Error:invalid zone");
			return null;
		}
		ArrayList<Zone> zones = new ArrayList<>();
		zones.add(zone);
		for (Zone z : ((FragmentedZone) zone).getSubZones()) {
			if (z instanceof FragmentedZone) {
				zones.addAll(getZonesFragmented(z));
			} else {
				zones.add(z);
			}
		}
		return zones;
	}
<<<<<<< HEAD
	
	
=======

>>>>>>> 1cd9b5ca3eae2f21b66106514195f08a9f18320b
}
