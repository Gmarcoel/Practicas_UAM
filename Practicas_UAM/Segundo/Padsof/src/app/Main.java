package app;

import events.*;
import performances.*;
import statistics.*;
import users.*;
import zones.*;
import java.io.*;
import java.time.*;
import java.util.*;

/**
 * This is a demonstrator class to show all the functionality of the application
 * 
 * @author Daniel Varela Sanchez 
 *		   daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class Main {

	public static void main(String[] args) throws IOException, ClassNotFoundException {
		TheaterApp app = new TheaterApp();
		// TheaterApp app = loader();

		app.ttp = 10;

		checkRegister(app);

		checkLogin(app);

		checkCreateEvent(app);

		checkSetZones(app);

		checkSetEventPrices(app);

		checkCreatePerformance(app);

		checkPostponePerformance(app);

		checkCancelPerformance(app);

		checkCancelEvent(app);

		checkSetCapacity(app);

		checkCreateCycle(app);

		checkSearchEvent(app);

		checkBookTicket(app);

		checkPurchaseSeat(app);

		checkMaintainSeat(app);

		checkAnnualPass(app);

		checkWaitList(app);

		checkPerformanceStatistics(app);

		showUsers(app);

		showEvents(app);

		showPasses(app);

		checkPersistance(app);

		checkPDF(app);
		
		System.out.println("End of test");
	}

	/**
	 * Method to load all the information of a theater app previously stored
	 * 
	 * @return app at the point where it was stored
	 * @throws FileNotFoundException  exception
	 * @throws IOException            exception
	 * @throws ClassNotFoundException exception
	 */
	private static TheaterApp loader() throws FileNotFoundException, IOException, ClassNotFoundException {
		ObjectInputStream in = new ObjectInputStream(new FileInputStream("./obj/" + "app" + ".objectData"));
		Object object = in.readObject();
		TheaterApp app = (TheaterApp) object;
		in.close();
		app.load();

		return app;
	}

	/**
	 * Method to check all the register functionality
	 * 
	 * @param app where we are working
	 */
	private static void checkRegister(TheaterApp app) {
		final String customer1Username = "Paco";
		final String customer1Password = "PacoPassword";
		final String customer2Username = "Miguel";
		final String customer2Password = "MiguePassword";
		final String adminUsername = "admin";
		final String adminPassword = "admin";

		System.out.println("-------------------------------------------------\n");
		System.out.println("\n\nStarting registration test :\n");
		// Test a registration with new credentials Paco
		if (app.register(customer1Username, customer1Password) == true) {
			System.out.println("\nRegistered new user\n  Username : " + app.getCustomer(customer1Username).getUsername()
					+ "\n  Password : " + app.getCustomer(customer1Username).getPassword());
		} else {
			System.out.println("\nUsername " + customer1Username + "Already exists");
		}

		// Test a registration with new credentials Miguel
		if (app.register(customer2Username, customer2Password) == true) {
			System.out.println("\nRegistered new user\n  Username : " + app.getCustomer(customer1Username).getUsername()
					+ "\n  Password : " + app.getCustomer(customer1Username).getPassword());
		} else {
			System.out.println("\nUsername " + customer1Username + "Already exists");
		}

		// Test a registration with existing admin credentials
		if (app.register(adminUsername, adminPassword) == true) {
			System.out.println("\nRegistered new user\n  Username : " + app.getCustomer(adminUsername).getUsername()
					+ "\n  Password : " + app.getCustomer(adminUsername).getPassword());
		} else {
			System.out.println("\nUsername " + customer1Username + "Already exists");
		}

		// Test a registration with already existing credentials
		if (app.register(customer1Username, customer1Password) == true) {
			System.out.println("\nRegistered new user\n  Username : " + app.getCustomer(customer1Username).getUsername()
					+ "\n  Password : " + app.getCustomer(customer1Username).getPassword());
		} else {
			System.out.println("\nUsername " + customer1Username + "Already exists");
		}
	}

	/**
	 * Method to check the login functionality
	 * 
	 * @param app where we are working
	 */
	private static void checkLogin(TheaterApp app) {
		final String customer1Username = "Paco";
		final String customer1Password = "PacoPassword";
		final String adminUsername = "admin";
		final String adminPassword = "admin";

		System.out.println("-------------------------------------------------\n");
		System.out.println("\n\nStarting login test :\n");
		// Test a customer login with correct credentials
		if (app.logIn(customer1Username, customer1Password) == true) {
			System.out.println("\nNew login by user\n  Username : " + app.getCustomer(customer1Username).getUsername()
					+ "\n  Password : " + app.getCustomer(customer1Username).getPassword());
		} else {
			System.out.println("\n  New login try failed\n  Username : " + customer1Username);
		}

		// Test a manager login with correct credentials
		if (app.logIn(adminUsername, adminPassword) == true) {
			System.out.println("\nNew login by admin\n  Username : " + app.getCustomer(adminUsername).getUsername()
					+ "\n  Password : " + app.getCustomer(adminUsername).getPassword());
		} else {
			System.out.println("\n  New login try failed\n  Username : " + adminUsername);
		}
	}

	/**
	 * Method to check the create event functionality
	 * 
	 * @param app where we are working
	 */
	private static void checkCreateEvent(TheaterApp app) {
		// Theater play variables
		final String theaterPlayTitle = "Title";
		final String theaterPlayAuthor = "Author";
		final String theaterPlayDirector = "Director";
		final String theaterPlayDescription = "Description";
		final String theaterPlayActors = "Actors";
		// Dance variables
		final String danceTitle = "DanceTitle";
		final String danceAuthor = "DanceAuthor";
		final String danceDirector = "danceDirector";
		final String danceDescription = "danceDescription";
		final String danceConductor = "danceConductor";
		final String danceDancers = "danceDancers";
		final String danceOrchestra = "danceOrchestra";
		// DancConcerte variables
		final String concertTitle = "concertTitle";
		final String concertAuthor = "concertAuthor";
		final String concertDirector = "concertDirector";
		final String concertDescription = "concertDescription";
		final String concertMusicPieces = "concertMusicPieces";
		final String concertOrchestra = "concertOrchestra";

		System.out.println("-------------------------------------------------\n");
		System.out.println("\n\nStarting Event creation test :\n");

		// test creating a theater play
		app.createPlayEvent(theaterPlayTitle, theaterPlayAuthor, theaterPlayDirector, theaterPlayDescription,
				theaterPlayActors, 88);
		if (app.getEvent(theaterPlayTitle) != null) {
			System.out.println("\nNew theater play created\n");
			System.out.println("  Title : " + app.getEvent(theaterPlayTitle).getTitle());
			System.out.println("   Author : " + app.getEvent(theaterPlayTitle).getAuthor());
			System.out.println("   Director : " + app.getEvent(theaterPlayTitle).getDirector());
			System.out.println("   Description : " + app.getEvent(theaterPlayTitle).getDescription());
			System.out.println("   Actors : " + ((TheaterPlay) app.getEvent(theaterPlayTitle)).getActors());
		}

		else {
			System.out.println("\nUnable to create theater play \n");
			System.out.println("  Title" + app.getEvent(theaterPlayTitle).getTitle());
		}

		// test creating a Dance event
		app.createDanceEvent(danceTitle, danceAuthor, danceDirector, danceDescription, danceConductor, danceDancers,
				danceOrchestra, 90);
		if (app.getEvent(theaterPlayTitle) != null) {
			System.out.println("\nNew theater play created\n");
			System.out.println("  Title : " + app.getEvent(danceTitle).getTitle());
			System.out.println("   Author : " + app.getEvent(danceTitle).getAuthor());
			System.out.println("   Director : " + app.getEvent(danceTitle).getDirector());
			System.out.println("   Description : " + app.getEvent(danceTitle).getDescription());
			System.out.println("   Conductor : " + ((Dance) app.getEvent(danceTitle)).getConductor());
			System.out.println("   Dancers : " + ((Dance) app.getEvent(danceTitle)).getDancer());
			System.out.println("   Orchestra : " + ((Dance) app.getEvent(danceTitle)).getOrchestra());
		} else {
			System.out.println("\nUnable to create theater play \n");
			System.out.println("  Title" + app.getEvent(theaterPlayTitle).getTitle());
		}

		// test creating a Concert event
		app.createConcertEvent(concertTitle, concertAuthor, concertDirector, concertDescription, concertMusicPieces,
				concertOrchestra, 120);
		if (app.getEvent(theaterPlayTitle) != null) {
			System.out.println("\nNew theater play created\n");
			System.out.println("  Title : " + app.getEvent(concertTitle).getTitle());
			System.out.println("   Author : " + app.getEvent(concertTitle).getAuthor());
			System.out.println("   Director : " + app.getEvent(concertTitle).getDirector());
			System.out.println("   Description : " + app.getEvent(concertTitle).getDescription());
			System.out.println("   Music Pieces : " + ((Concert) app.getEvent(concertTitle)).getMusicPieces());
			System.out.println("   Orchestra : " + ((Concert) app.getEvent(concertTitle)).getOrchestra());
		} else {
			System.out.println("\nUnable to create theater play \n");
			System.out.println("  Title" + app.getEvent(theaterPlayTitle).getTitle());
		}
	}

	/**
	 * Method to check the create performance functionality
	 * 
	 * @param app where we are working
	 */
	private static void checkCreatePerformance(TheaterApp app) {
		final String theaterPlayTitle = "Title";
		final String danceTitle = "DanceTitle";
		final String concertTitle = "concertTitle";

		System.out.println("-------------------------------------------------\n");
		System.out.println("\n\nStarting performance creation test :\n");

		System.out.println("\nSet performances for theater play: " + theaterPlayTitle);
		// we create a performance for theater play set to th 17/9/2021 at 10:30
		app.createPerformance(app.getEvent(theaterPlayTitle), LocalDateTime.of(2021, 9, 17, 10, 30));
		// we create a performance for theater play set to th 26/9/2021 at 19:15
		app.createPerformance(app.getEvent(theaterPlayTitle), LocalDateTime.of(2021, 9, 26, 19, 15));
		// we create a performance for theater play set to th 6/10/2021 at 20:45
		app.createPerformance(app.getEvent(theaterPlayTitle), LocalDateTime.of(2021, 10, 6, 20, 45));
		for (Performance p : app.getEvent(theaterPlayTitle).getPerformances()) {
			System.out.println("    Performance:" + p.getDate());
		}

		System.out.println("\nSet performances for dance: " + danceTitle);
		// we create a performance for dance set to th 7/1/2022 at 21:30
		app.createPerformance(app.getEvent(danceTitle), LocalDateTime.of(2022, 1, 7, 21, 30));
		// we create a performance for dance set to th 14/1/2022 at 19:15
		app.createPerformance(app.getEvent(danceTitle), LocalDateTime.of(2022, 1, 14, 19, 15));
		// we create a performance for dance set to th 19/12/2021 at 18:10
		app.createPerformance(app.getEvent(danceTitle), LocalDateTime.of(2021, 12, 19, 18, 10));
		for (Performance p : app.getEvent(theaterPlayTitle).getPerformances()) {
			System.out.println("    Performance:" + p.getDate());
		}

		System.out.println("\nSet performances for concert: " + concertTitle);
		// we create a performance for concert set to th 10/7/2021 at 15:30
		app.createPerformance(app.getEvent(concertTitle), LocalDateTime.of(2021, 7, 10, 15, 30));
		// we create a performance for concert set to th 2/9/2021 at 18:15
		app.createPerformance(app.getEvent(concertTitle), LocalDateTime.of(2021, 9, 2, 18, 15));
		// we create a performance for concert set to th 6/10/2021 at 17:45
		app.createPerformance(app.getEvent(concertTitle), LocalDateTime.of(2021, 8, 8, 17, 45));
		for (Performance p : app.getEvent(theaterPlayTitle).getPerformances()) {
			System.out.println("    Performance:" + p.getDate());
		}

	}

	/**
	 * Method to check the postpone performance functionality
	 * 
	 * @param app where we are working
	 */
	private static void checkPostponePerformance(TheaterApp app) {
		final String danceTitle = "DanceTitle";

		System.out.println("-------------------------------------------------\n");
		System.out.println("\n\nStarting performance postpone test :\n");
		System.out.println("\n\nModify the first performance date to be 4/2/2021 at 17:15 :\n");

		System.out.println("\nPerformances for dance event : " + danceTitle);

		for (Performance p : app.getEvent(danceTitle).getPerformances()) {
			System.out.println("    Performance:" + p.getDate());
		}
		// The second performance should change its date from 7/1/2022 at 21:30 to
		// 4/2/2021 at 17:15
		app.postponePerformace(app.getEvent(danceTitle).getPerformance(LocalDateTime.of(2022, 1, 7, 21, 30)),
				LocalDateTime.of(2022, 2, 4, 17, 30));

		System.out.println("\nPerformances after postpone : " + danceTitle);

		for (Performance p : app.getEvent(danceTitle).getPerformances()) {
			System.out.println("    Performance:" + p.getDate());
		}
	}

	/**
	 * Method to check the cancel performance functionality
	 * 
	 * @param app where we are working
	 */
	private static void checkCancelPerformance(TheaterApp app) {
		final String danceTitle = "DanceTitle";

		System.out.println("-------------------------------------------------\n");
		System.out.println("\n\nStarting performance cancel test :\n");
		System.out.println("\n\nDelete the third performance\n");

		System.out.println("\nPerformances for dance event : " + danceTitle);

		for (Performance p : app.getEvent(danceTitle).getPerformances()) {
			System.out.println("    Performance:" + p.getDate());
		}
		// The third performance should be cancelled
		app.cancelPerformance(app.getEvent(danceTitle).getPerformance(LocalDateTime.of(2022, 1, 7, 21, 30)));

		System.out.println("\nPerformances after cancelling : " + danceTitle);

		for (Performance p : app.getEvent(danceTitle).getPerformances()) {
			System.out.println("    Performance:" + p.getDate());
		}
	}

	/**
	 * Method to check the cancel event functionality
	 * 
	 * @param app where we are working
	 */
	private static void checkCancelEvent(TheaterApp app) {
		final String danceTitle = "DanceTitle";

		System.out.println("-------------------------------------------------\n");
		System.out.println("\n\nStarting event cancel test :\n");
		System.out.println("\nPrint events before cancelling: ");
		for (Event e : app.getEvents()) {
			System.out.println("    " + e.getTitle());
		}
		System.out.println("\n\nCanceling dance event  : " + danceTitle + "\n");

		// The dance event should be canceled and not apear
		app.cancelEvent(app.getEvent(danceTitle));
		System.out.println("\nPrint events after cancelling: ");
		for (Event e : app.getEvents()) {
			System.out.println("    " + e.getTitle());
		}
	}

	/**
	 * Method to check the set zones functionality
	 * 
	 * @param app where we are working
	 */
	public static void checkSetZones(TheaterApp app) {
		final String SittingZone1 = "SittingZone1";
		final String StandingZone1 = "StandingZone1";
		final String Fragmented1 = "Fragmented1";
		final String SittingZone2 = "SittingZone2";
		final String Fragmented2 = "Fragmented2";
		final String StandingZone2 = "StandingZone2";

		System.out.println("-------------------------------------------------\n");
		System.out.println("Creating zones:\n");
		// We create a sitting zone called SittingZone1 with 1 row 5 columns and a
		// price for the anual pass of 300
		app.createSittingZone(SittingZone1, 1, 5, 300);
		System.out.println("  Zone +" + app.getZone(SittingZone1).getName() + " created");
		// We create a standing zone called StandingZone1 that can fit 20 people and a
		// price for the anual pass of 100
		app.createStandingZone(StandingZone1, 20, 100);
		System.out.println("  Zone +" + app.getZone(StandingZone1).getName() + " created");
		// We create a Fragmented zone called Fragmented1 that will contain a sitting
		// zone inside and another fragmented zone
		app.createFragmentedZone(Fragmented1);
		System.out.println("  Zone +" + app.getZone(Fragmented1).getName() + " created");
		// We create a sitting zone called SittingZone2 inside a fragmented zone
		// Fragemnted1 with 2 rows 2 columns and a price for the anual pass of 270
		app.createSittingZone(SittingZone2, 2, 2, Fragmented1, 270);
		System.out.println(
				"  Zone +" + app.getZone(SittingZone1).getName() + " created inside " + app.getZone(Fragmented1));
		// We create a fragmented zone Fragmented2 inside the fragmented zone
		// Fragmented1
		app.createFragmentedZone(Fragmented2, Fragmented1);
		System.out.println(
				"  Zone +" + app.getZone(Fragmented2).getName() + " created inside " + app.getZone(Fragmented1));
		// We create a standing zone called StandingZone2 inside a fragmented zone
		// Fragemnted2 inside FragmentedZone1 with capacity of 2 pereople and a price
		// for the anual pass of 600
		app.createStandingZone(StandingZone2, 2, Fragmented2, 600);
		System.out.println(
				"  Zone +" + app.getZone(StandingZone2).getName() + " created inside " + app.getZone(Fragmented2));
	}

	/**
	 * Method to check the set prices functionality
	 * 
	 * @param app where we are working
	 */
	public static void checkSetEventPrices(TheaterApp app) {
		// Event attributes
		final String theaterPlayTitle = "Title";
		final String danceTitle = "DanceTitle";
		final String concertTitle = "concertTitle";
		// Zone attributes
		final String SittingZone1 = "SittingZone1";
		final String StandingZone1 = "StandingZone1";
		final String SittingZone2 = "SittingZone2";
		final String StandingZone2 = "StandingZone2";
		app.initializePrices(app.getEvent(theaterPlayTitle));

		System.out.println("-------------------------------------------------\n");
		System.out.println("Setting prices:\n");
		// We add a price of 20 for the SitingZone1 in the theater play
		app.setPrice(theaterPlayTitle, SittingZone1, 20);
		System.out.println("  Set price " + app.getEvent(theaterPlayTitle).getPrice(app.getZone(SittingZone1))
				+ " for event : " + app.getEvent(theaterPlayTitle).getTitle() + " and zone " + SittingZone1);
		// We add a price of 24 for the StandingZone1
		app.setPrice(theaterPlayTitle, StandingZone1, 24);
		System.out.println("  Set price " + app.getEvent(theaterPlayTitle).getPrice(app.getZone(StandingZone1))
				+ " for event : " + app.getEvent(theaterPlayTitle).getTitle() + " and zone " + StandingZone1);
		// We add a price of 26 for the SittingZone2
		app.setPrice(theaterPlayTitle, SittingZone2, 26);
		System.out.println("  Set price " + app.getEvent(theaterPlayTitle).getPrice(app.getZone(SittingZone2))
				+ " for event : " + app.getEvent(theaterPlayTitle).getTitle() + " and zone " + SittingZone2);
		// We add a price of 30 for the StandingZone2
		app.setPrice(theaterPlayTitle, StandingZone2, 30);
		System.out.println("  Set price " + app.getEvent(theaterPlayTitle).getPrice(app.getZone(StandingZone2))
				+ " for event : " + app.getEvent(theaterPlayTitle).getTitle() + " and zone " + StandingZone2);

		System.out.println("\n");
		app.initializePrices(app.getEvent(danceTitle));
		// We add a price of 20 for the SitingZone1 in the dance event
		app.setPrice(danceTitle, SittingZone1, 9);
		System.out.println("  Set price " + app.getEvent(danceTitle).getPrice(app.getZone(SittingZone1))
				+ " for event : " + app.getEvent(danceTitle).getTitle() + " and zone " + SittingZone1);
		// We add a price of 20 for the StandingZone1 in the dance event
		app.setPrice(danceTitle, StandingZone1, 27);
		System.out.println("  Set price " + app.getEvent(danceTitle).getPrice(app.getZone(StandingZone1))
				+ " for event : " + app.getEvent(danceTitle).getTitle() + " and zone " + StandingZone1);
		// We add a price of 20 for the SittingZone2 in the dance event
		app.setPrice(danceTitle, SittingZone2, 12);
		System.out.println("  Set price " + app.getEvent(danceTitle).getPrice(app.getZone(SittingZone2))
				+ " for event : " + app.getEvent(danceTitle).getTitle() + " and zone " + SittingZone2);
		// We add a price of 30 for the StandingZone2
		app.setPrice(danceTitle, StandingZone2, 30);
		System.out.println("  Set price " + app.getEvent(danceTitle).getPrice(app.getZone(StandingZone2))
				+ " for event : " + app.getEvent(danceTitle).getTitle() + " and zone " + StandingZone2);

		System.out.println("\n");
		app.initializePrices(app.getEvent(concertTitle));
		// We add a price of 20 for the SitingZone1 in the concert event
		app.setPrice(concertTitle, SittingZone1, 15);
		System.out.println("  Set price " + app.getEvent(concertTitle).getPrice(app.getZone(SittingZone1))
				+ " for event : " + app.getEvent(concertTitle).getTitle() + " and zone " + SittingZone1);
		// We add a price of 20 for the StandingZone1 in the concert event
		app.setPrice(concertTitle, StandingZone1, 20);
		System.out.println("  Set price " + app.getEvent(concertTitle).getPrice(app.getZone(StandingZone1))
				+ " for event : " + app.getEvent(concertTitle).getTitle() + " and zone " + StandingZone1);
		// We add a price of 26 for the SittingZone2
		app.setPrice(concertTitle, SittingZone2, 16);
		System.out.println("  Set price " + app.getEvent(concertTitle).getPrice(app.getZone(SittingZone2))
				+ " for event : " + app.getEvent(concertTitle).getTitle() + " and zone " + SittingZone2);
		// We add a price of 30 for the StandingZone2
		app.setPrice(concertTitle, StandingZone2, 17);
		System.out.println("  Set price " + app.getEvent(concertTitle).getPrice(app.getZone(StandingZone2))
				+ " for event : " + app.getEvent(concertTitle).getTitle() + " and zone " + StandingZone2);

	}

	/**
	 * Method to check the set capacity functionality
	 * 
	 * @param app where we are working
	 */
	private static void checkSetCapacity(TheaterApp app) {
		System.out.println("-------------------------------------------------\n");
		System.out.println("Setting the theater occupancy to 70%\n");
		app.setOccupancy(70);
	}

	/**
	 * Method to check the booking functionality
	 * 
	 * @param app where we are working
	 */
	private static void checkBookTicket(TheaterApp app) {
		final String theaterPlayTitle = "Title";
		final String concertTitle = "concertTitle";
		System.out.println("-------------------------------------------------\n");

		System.out.println("Booking a ticket for event : " + theaterPlayTitle + " for user "
				+ app.getCustomer("Paco").getUsername());
		app.bookTicket(((Customer) app.getCustomer("Paco")),
				app.getPerformance(theaterPlayTitle, LocalDateTime.of(2021, 9, 17, 10, 30))
						.selectTicketWithString("SittingZone1", 0, 1));

		System.out.println(
				"Booking a ticket for event : " + concertTitle + " for user " + app.getCustomer("Paco").getUsername());
		app.bookTicket(((Customer) app.getCustomer("Paco")),
				app.getPerformance(concertTitle, LocalDateTime.of(2021, 7, 10, 15, 30))
						.selectTicketWithString("SittingZone2", 0, 1));

		System.out.println("Booking a ticket for event : " + theaterPlayTitle + " for user "
				+ app.getCustomer("Miguel").getUsername());
		app.bookTicket(((Customer) app.getCustomer("Miguel")),
				app.getPerformance(theaterPlayTitle, LocalDateTime.of(2021, 9, 17, 10, 30))
						.selectTicketWithString("SittingZone2", 1, 0));
	}

	/**
	 * Method to check the search functionality
	 * 
	 * @param app where we are working
	 */
	private static void checkSearchEvent(TheaterApp app) {
		System.out.println("-------------------------------------------------\n");
		System.out.println("Print the Theater Plays: ");
		System.out.println("\n");
		for (Event e : app.searchEvent(0)) {
			System.out.println("	" + e.getTitle());
		}
		System.out.println("\n");
		System.out.println("Print the Dances: ");
		for (Event e : app.searchEvent(1)) {
			System.out.println("	" + e.getTitle());
		}
		System.out.println("\n");
		System.out.println("Print the Concerts : ");
		for (Event e : app.searchEvent(2)) {
			System.out.println("	" + e.getTitle());
		}
	}

	/**
	 * Method to check the maintenance functionality
	 * 
	 * @param app where we are working
	 */
	private static void checkMaintainSeat(TheaterApp app) {
		app.mantainSeat("SittingZone1", 0, 3, LocalDate.of(2021, 9, 17), "The seat is broken");
		app.mantainSeat("SittingZone2", 1, 0, LocalDate.of(2022, 9, 18), "The seat is fully broken");
	}

	/**
	 * Method to check the annual pass functionality
	 * 
	 * @param app where we are working
	 */
	private static void checkAnnualPass(TheaterApp app) {
		final String theaterPlayTitle = "Title";
		final String concertTitle = "concertTitle";

		System.out.println("-------------------------------------------------\n");
		System.out.println("Checking annual pass:\n");
		app.payPassWithCard(((Customer) app.getCustomer("Paco")), app.getZone("StandingZone1"), "1234567890123456");

		System.out.println("The purchase result of buying a possible ticket is :" + app.payWithPass(
				((Customer) app.getCustomer("Paco")), ((Customer) app.getCustomer("Paco")).getAnnualPass(),
				app.getEvent(concertTitle), app.getPerformance(concertTitle, LocalDateTime.of(2021, 7, 10, 15, 30))
						.selectTicketWithString("StandingZone1")));
		System.out.println("The purchase result of buying a possible ticket is :"
				+ app.payWithPass(((Customer) app.getCustomer("Paco")),
						((Customer) app.getCustomer("Paco")).getAnnualPass(), app.getEvent(theaterPlayTitle),
						app.getPerformance(theaterPlayTitle, LocalDateTime.of(2021, 10, 6, 20, 45))
								.selectTicketWithString("StandingZone1")));
		System.out.println("The purchase result of trying to purchase a ticket for an already attended event is : "
				+ app.payWithPass(((Customer) app.getCustomer("Paco")),
						((Customer) app.getCustomer("Paco")).getAnnualPass(), app.getEvent(concertTitle),
						app.getPerformance(concertTitle, LocalDateTime.of(2021, 7, 10, 15, 30))
								.selectTicketWithString("StandingZone1")));
		System.out.println(
				"The purchase result of trying to purchase a ticket with a different zone from the annual pass is :"
						+ app.payWithPass(((Customer) app.getCustomer("Paco")),
								((Customer) app.getCustomer("Paco")).getAnnualPass(), app.getEvent(theaterPlayTitle),
								app.getPerformance(theaterPlayTitle, LocalDateTime.of(2021, 10, 6, 20, 45))
										.selectTicketWithString("SittingZone1", 0, 0)));

	}

	/**
	 * Method to check the create cycle functionality
	 * 
	 * @param app where we are working
	 */
	private static void checkCreateCycle(TheaterApp app) {
		app.createCycle("Operas by P.Lag.");
		Cycle c = (Cycle) (app.getEvent("Operas by P.Lag."));
		app.addEventToCycle(app.getEvent("Title"), c);
		System.out.println("-------------------------------------------------\n");
		System.out.println("Creating cycle Operas by P.Lag.\n");
		app.createCyclePass("Summer pass", 50, app.getZone("StandingZone2"), c);
		System.out.println("Customer Miguel buys Summer pass\n");
		app.payPassWithCard((Customer) app.getCustomer("Miguel"), app.getPass("Summer pass"), "1234567890123456");
		for (Pass p : ((Customer) app.getCustomer("Miguel")).getPasses()) {
			System.out.println("Miguel Passes: " + p.getName());
		}
	}

	/**
	 * Method to check the purchase seat functionality
	 * 
	 * @param app where we are working
	 */
	private static void checkPurchaseSeat(TheaterApp app) {

		System.out.println("-------------------------------------------------\n");

		System.out.println("Miguel buys with Summer pass");
		boolean b = app.payWithPass(((Customer) app.getCustomer("Miguel")),
				((Customer) app.getCustomer("Miguel")).getPass("Summer pass"), app.getEvent("Title"),
				(app.getPerformance("Title", LocalDateTime.of(2021, 9, 17, 10, 30))).selectTicket(
						app.getPerformance("Title", LocalDateTime.of(2021, 9, 17, 10, 30)).getZone("StandingZone2")));
		System.out.println("Purchase with pass: " + b);
		System.out.println("Miguel buys booked with creddit card");
		app.payTicketWithCard((Customer) app.getCustomer("Miguel"), app.getEvent("Title"),
				((Customer) app.getCustomer("Miguel")).getTicket(20210919), "1234567890123456");

	}

	/**
	 * Method to check the performance statistics functionality
	 * 
	 * @param app where we are working
	 */
	private static void checkPerformanceStatistics(TheaterApp app) {
		app.updatePerformanceZoneStatistic("Title", LocalDateTime.of(2021, 9, 17, 10, 30), "SittingZone1");
		System.out.println("-------------------------------------------------\n");
		System.out.println("Performance Zone Statistic Title 17/09/2021 10:30 SittingZone1");
		System.out.println("	Occupancy: " + app.getZoneStatistic("SittingZone1").getOccupancy());
		System.out.println("	   Profit: " + app.getZoneStatistic("SittingZone1").getProfits());
		System.out.println("\n");
		app.updateEventZoneStatistic("Title", "SittingZone1");
		System.out.println("Event Zone Statistic Title SittingZone1");
		System.out.println("	Occupancy: " + app.getZoneStatistic("SittingZone1").getOccupancy());
		System.out.println("	   Profit: " + app.getZoneStatistic("SittingZone1").getProfits());
		System.out.println("\n");
		app.updateZoneStatistic("SittingZone1");
		System.out.println("Zone Statistic Title SittingZone1");
		System.out.println("	Occupancy: " + app.getZoneStatistic("SittingZone1").getOccupancy());
		System.out.println("	   Profit: " + app.getZoneStatistic("SittingZone1").getProfits());
		System.out.println("\n");
		app.updateEventStatistic("Title");
		System.out.println("Event Statistic Title ");
		System.out.println("	Occupancy: " + app.getEventStatistic("Title").getOccupancy());
		System.out.println("	   Profit: " + app.getEventStatistic("Title").getProfits());
		System.out.println("\n");
		app.updatePerformanceStatistic("Title", LocalDateTime.of(2021, 9, 17, 10, 30));
		System.out.println("Performance Statistic Title  17/09/2021 10:30");
		System.out.println("	Occupancy: "
				+ app.getPerformanceStatistic("Title", LocalDateTime.of(2021, 9, 17, 10, 30)).getOccupancy());
		System.out.println("	   Profit: "
				+ app.getPerformanceStatistic("Title", LocalDateTime.of(2021, 9, 17, 10, 30)).getProfits());
		System.out.println("\n");
	}

	/**
	 * Method to check the waitlist functionality
	 * 
	 * @param app where we are working
	 */
	private static void checkWaitList(TheaterApp app) {
		final String secondTheaterPlayTitle = "Second Title";
		final String theaterPlayAuthor = "Author1";
		final String theaterPlayDirector = "Director1";
		final String theaterPlayDescription = "Description1";
		final String theaterPlayActors = "Actors1";
		System.out.println("------------------------------");
		// test creating a theater play
		app.createPlayEvent(secondTheaterPlayTitle, theaterPlayAuthor, theaterPlayDirector, theaterPlayDescription,
				theaterPlayActors, 200);
		if (app.getEvent(secondTheaterPlayTitle) != null) {
			System.out.println("\nNew theater play created\n");
			System.out.println("  Title : " + app.getEvent(secondTheaterPlayTitle).getTitle());
			System.out.println("   Author : " + app.getEvent(secondTheaterPlayTitle).getAuthor());
			System.out.println("   Director : " + app.getEvent(secondTheaterPlayTitle).getDirector());
			System.out.println("   Description : " + app.getEvent(secondTheaterPlayTitle).getDescription());
			System.out.println("   Actors : " + ((TheaterPlay) app.getEvent(secondTheaterPlayTitle)).getActors());
		}

		else {
			System.out.println("\nUnable to create theater play \n");
			System.out.println("  Title" + app.getEvent(secondTheaterPlayTitle).getTitle());
		}
		app.createPerformance(app.getEvent(secondTheaterPlayTitle), LocalDateTime.of(2021, 10, 1, 18, 30));


		System.out.println("The result of trying to subscribe to the waitlist of a performance that is not full : "+app.suscribeToWaitList(((Customer)app.getCustomer("Miguel")),
				app.getPerformance(secondTheaterPlayTitle, LocalDateTime.of(2021, 10, 1, 18, 30))));

		app.getEvent(secondTheaterPlayTitle).getPerformance(LocalDateTime.of(2021, 10, 1, 18, 30)).getZone("SittingZone1").setOccupancy(0);
		app.getEvent(secondTheaterPlayTitle).getPerformance(LocalDateTime.of(2021, 10, 1, 18, 30)).getZone("SittingZone2").setOccupancy(0);
		app.getEvent(secondTheaterPlayTitle).getPerformance(LocalDateTime.of(2021, 10, 1, 18, 30)).getZone("StandingZone1").setOccupancy(0);
		app.getEvent(secondTheaterPlayTitle).getPerformance(LocalDateTime.of(2021, 10, 1, 18, 30)).getZone("StandingZone2").setOccupancy(0);

		System.out.println("The result of trying to subscribe to the waitlist of a full performance : "+app.suscribeToWaitList(((Customer)app.getCustomer("Miguel")),
				app.getPerformance(secondTheaterPlayTitle, LocalDateTime.of(2021, 10, 1, 18, 30))));

		System.out.println("Wishlist of "+secondTheaterPlayTitle);
		for(RegisteredUser c : app.getPerformance(secondTheaterPlayTitle, LocalDateTime.of(2021, 10, 1, 18, 30)).getWaitList().getCustomers()){
			System.out.println("	"+c.getUsername());
		}
	}

	/**
	 * Method to check the show events functionality
	 * 
	 * @param app where we are working
	 */
	public static void showEvents(TheaterApp app) {
		System.out.println("-------------------------------------------------\n");
		System.out.println("Printing all Events:\n");
		System.out.println("Events: ");
		for (Event e : app.getEvents()) {
			if (e instanceof Cycle) {
				showCycles(e, 0);
			} else {
				System.out.println("  " + e.getTitle());
				System.out.println("    Performances: ");
				for (Performance p : e.getPerformances()) {
					System.out.println("      " + p.getDate());
					System.out.println("        Zones: ");
					for (Zone z : p.getZones()) {
						if (z instanceof FragmentedZone) {
							System.out.println("          " + z.getName() + " [" + ((FragmentedZone) z).getAttendees()
									+ "/" + ((FragmentedZone) z).getNPosPeople() + "/"
									+ ((FragmentedZone) z).getNMaxPeople() + "]");
							printSubZones(z, e, 1);
						} else {
							System.out.println("          " + z.getName() + " [" + z.getAttendees() + "/"
									+ z.getNPosPeople() + "/" + z.getNMaxPeople() + "] Price: " + e.getPrice(z));
						}
						if (z instanceof SittingZone) {
							for (Seat[] sr : ((SittingZone) z).getMatrix()) {
								for (Seat s : sr) {
									if (s.getMSeat() != null) {
										System.out.println("            [" + s.getNRow() + ", " + s.getNColumn()
												+ "] In maintenance untill " + s.getMSeat().getEndDate() + " //"
												+ s.getMSeat().getNotes());
									} else {
										System.out.println(
												"            [" + s.getNRow() + ", " + s.getNColumn() + "] Occupied : "
														+ s.getOccupied() + " - Available : " + s.getAvailable());

									}
								}
							}
						}
					}
				}
			}
		}
	}

	/**
	 * Method to check the subzones functionality
	 * 
	 * @param zone zone
	 * @param e event
	 * @param depth depth to print
	 */
	public static void printSubZones(Zone zone, Event e, int depth) {
		String tabs = "          ";
		for (int i = 0; i < depth; i++) {
			tabs += "	";
		}
		for (Zone z : ((FragmentedZone) zone).getSubZones()) {
			if (z instanceof FragmentedZone) {
				System.out.println(tabs + z.getName() + " [" + ((FragmentedZone) z).getAttendees() + "/"
						+ ((FragmentedZone) z).getNPosPeople() + "/" + ((FragmentedZone) z).getNMaxPeople() + "]");
				printSubZones(z, e, depth + 1);
			} else {
				System.out.println(tabs + z.getName() + " [" + z.getAttendees() + "/" + z.getNPosPeople() + "/"
						+ z.getNMaxPeople() + "] Price: " + e.getPrice(z));
			}
			if (z instanceof SittingZone) {
				for (Seat[] sr : ((SittingZone) z).getMatrix()) {
					for (Seat s : sr) {
						if (s.getMSeat() != null) {
							System.out.println(
									tabs + "[" + s.getNRow() + ", " + s.getNColumn() + "] In maintenance untill "
											+ s.getMSeat().getEndDate() + " //" + s.getMSeat().getNotes());
						} else {
							System.out.println(tabs + "[" + s.getNRow() + ", " + s.getNColumn() + "] Occupied : "
									+ s.getOccupied() + " - Available : " + s.getAvailable());

						}
					}
				}
			}
		}
	}

	/**
	 * Method to check the cycles functionality
	 * 
	 * @param event where we are working
	 * @param depth where we are working
	 */
	public static void showCycles(Event event, int depth) {
		String tabs = "  ";
		for (int i = 0; i < depth; i++) {
			tabs += "	";
		}
		System.out.println(tabs + "Cycle : " + event.getTitle());
		for (Event e : ((Cycle) event).getEvents()) {
			if (e instanceof Cycle) {
				showCycles(e, depth + 1);
			} else {
				System.out.println(tabs + "	" + e.getTitle());
			}
		}
	}

	/**
	 * Method to check the users functionality
	 * 
	 * @param app where we are working
	 */
	public static void showUsers(TheaterApp app) {
		System.out.println("-------------------------------------------------\n");
		System.out.println("Printing all users:\n");
		System.out.println("Users: ");
		for (RegisteredUser u : app.getUsers()) {
			System.out.println("  Username : " + u.getUsername());
			System.out.println("  Password : " + u.getPassword());
			if (u instanceof Customer) {
				for (Pass p : ((Customer) u).getPasses()) {
					System.out.println("      Pass : " + p.getName() + " [Zone : " + p.getZone().getName()
							+ ", Price : " + p.getPrice() + "]");
				}
				for (Ticket t : ((Customer) u).getTickets()) {
					if (t.getZone() instanceof SittingZone) {
						System.out.println("      Ticket : " + t.getCode());
						System.out.println("      	Puchased :" + t.getPurchased());
						System.out.println("      	Event :" + t.getPerformance().getEventTitle());
						System.out.println("      	Performance :" + t.getPerformance().getDate());
						System.out.println("      	Zone :" + t.getZone().getName());
						System.out.println(
								"      	Row : " + t.getSeat().getNRow() + " Column : " + t.getSeat().getNColumn());
					}
					if (t.getZone() instanceof StandingZone) {
						System.out.println("      Ticket : " + t.getCode());
						System.out.println("      	Puchased :" + t.getPurchased());
						System.out.println("      	Event :" + t.getPerformance().getEventTitle());
						System.out.println("      	Performance :" + t.getPerformance().getDate());
						System.out.println("      	Zone :" + t.getZone().getName());
					}
				}
			}
		}
	}

	/**
	 * Method to check the passes functionality
	 * 
	 * @param app where we are working
	 */
	public static void showPasses(TheaterApp app) {
		System.out.println("-------------------------------------------------\n");
		System.out.println("Printing all passes:\n");
		for (RegisteredUser c : app.getUsers()) {
			if (c instanceof Customer) {
				for (Pass p : ((Customer) c).getPasses()) {
					System.out.println("Pass" + p.getName());
					System.out.println("	zone:  " + p.getZone().getName());
					System.out.println("	price: " + p.getPrice());
					if (p instanceof CyclePass) {
						System.out.println("	type: CyclePass");
						System.out.println("	Available Events:");
						for (Event e : ((CyclePass) p).getCanGoToList()) {
							System.out.println("		" + e.getTitle());
						}
					}
					System.out.println("	Already attended events:");
					for (Event e : p.getAlreadyAttendedList()) {
						System.out.println("		" + e.getTitle());
					}
				}
			}
		}
	}
	/**
	 * Saves and loads serializable objects to check persistance if works correctly
	 * 
	 * @param app theater app to copy
	 * @throws IOException exception
	 * @throws ClassNotFoundException exception
	 */
	public static void checkPersistance(TheaterApp app) throws IOException, ClassNotFoundException {
		System.out.println("------------------------------");
		app.save();
		app = null;
		app = loader();
		showEvents(app);
		showPasses(app);
		showUsers(app);
		System.out.println("------------------------------");
		
	}
	
	/**
	 * Save ticket to pdf test
	 * 
	 * @param app theater app of the corresponding ticket to print
	 */
	public static void checkPDF(TheaterApp app) {
		//This should generate a pdf for the ticket 20210919 owned by miguel
		((Customer)app.getCustomer("Miguel")).getTicket(20210919).generateTicketPDF();
	}
}
