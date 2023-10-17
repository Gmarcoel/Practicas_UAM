package app;

import zones.*;
import events.*;
import users.*;
import performances.*;
import statistics.*;

import java.util.*;
import java.time.*;
import java.io.*;

import static org.junit.Assert.*;

import org.junit.Test;
import org.junit.Before;

public class TheaterAppTest {

	TheaterApp ta;
	Customer c1;
	Customer c2;
	Customer c3;
	Manager m;
	StandingZone stz1;
	StandingZone stz2;
	StandingZone stz3;
	SittingZone sz1;
	SittingZone sz2;
	SittingZone sz3;
	FragmentedZone fz1;
	FragmentedZone fz2;
	ZoneStatistic stats1;
	ZoneStatistic stats2;
	ZoneStatistic stats3;
	Dance e1;
	Concert e2;
	TheaterPlay e3;
	StandingZone z1;
	SittingZone z2;
	Performance p1;
	Performance p2;
	Performance p3;
	Ticket t1;
	Ticket t2;
	Ticket t3;
	ArrayList<Zone> zones;
	ArrayList<Price> apPrice;
	AnnualPass ap1;
	CyclePass cp1;
	Cycle cycle1;
	Cycle cycle2;
	Price price1;

	@Before
	public void before() {
		ta = new TheaterApp();
		ta.register("Paco", "pacopassword");
		c1 = new Customer("Paco", "pacopassword");
		c2 = new Customer("Pepe Lagartija", "pepeLagarto");
		c3 = new Customer("Miguel", "contrasena");
		m = new Manager();
		ta.getUsers().add(m);
		ta.getUsers().add(c1);
		ta.getUsers().add(c2);

		
		stz1 = new StandingZone("Standing 1", 10);
		stz2 = new StandingZone("Standing 2", 15);
		stz3 = new StandingZone("Standing 3", 20);
		sz1 = new SittingZone("Sitting 1", 2, 2);
		sz2 = new SittingZone("Sitting 2", 3, 2);
		sz3 = new SittingZone("Sitting 3", 2, 4);
		fz1 = new FragmentedZone("Fragmented 1");
		fz2 = new FragmentedZone("Fragmented 2");

		ta.createFragmentedZone("Fragmented 1");
		ta.createFragmentedZone("Fragmented 2", "Fragmented 1");
		
	
		ta.createStandingZone("Standing 1", 10, "Fragmented 1", 30);
		ta.createStandingZone("Standing 2", 15, "Fragmented 2", 40);
		ta.createStandingZone("Standing 3", 20, 70);

		ta.createSittingZone("Sitting 1", 2, 2, "Fragmented 1", 500);
		ta.createSittingZone("Sitting 2", 3, 2, "Fragmented 2", 500);
		ta.createSittingZone("Sitting 3", 2, 4, 500);

		ta.annualPassPrice.add(new Price(stz1, 100));
		ta.annualPassPrice.add(new Price(stz2, 120));
		ta.annualPassPrice.add(new Price(stz3, 130));
		ta.annualPassPrice.add(new Price(sz1, 200));
		ta.annualPassPrice.add(new Price(sz2, 220));
		ta.annualPassPrice.add(new Price(sz3, 250));

		fz1.addSubzone(stz1);
		fz1.addSubzone(sz1);
		fz1.addSubzone(fz2);

		fz2.addSubzone(stz2);
		fz2.addSubzone(sz2);

		zones = new ArrayList<>();
		zones.add(fz1);
		zones.add(stz3);
		zones.add(sz3);

		stats1 = new ZoneStatistic("Stats 1", fz1);
		stats2 = new ZoneStatistic("Stats 2", sz3);
		stats3 = new ZoneStatistic("Stats 3", stz3);

		price1= new Price(sz3,20);
		
		ta.createDanceEvent("Swan lake", "Dostoievski", "Pepe Lagartija", "Beautiful movements", "Messi",
				"Richard Widmark", "National Band", 120);

		e1 = ((Dance) ta.getEvent("Swan lake"));
		
		e1.addPrice(price1);
		
		e2 = new Concert("RDR2 Soundtrack", "D'Angelo", "Pepe Lagartija", "Musical masterpiece",
				"Unshaken, Cruel World, Moonlight", "National Band");
		e3 = new TheaterPlay("Romeo & Juliet", "Shakespeare", "Pepe Lagartija", "Two lovers, one destiny",
				"Danielo, Guillerma");

		ta.getEvents().add(e2);
		ta.getEvents().add(e3);

		z1 = new StandingZone("Zone 1", 20);
		z2 = new SittingZone("Zone 2", 4, 4);

		ta.getEvent("Swan lake").createPerformance(LocalDateTime.of(2021, 7, 27, 7, 00), zones);
		p1 = ta.getEvent("Swan lake").getPerformance(LocalDateTime.of(2021, 7, 27, 7, 00));
		p2 = new Performance(LocalDateTime.of(2021, 11, 12, 10, 30), zones, ta.getEvent("Swan lake"));
		e1.getPerformances().add(p1);
		e1.getPerformances().add(p2);
		t1 = new Ticket(p2.getZone(sz3), ((SittingZone) p2.getZone(sz3)).getSeat(1, 1), p2);
		t2 = e1.getPerformance(LocalDateTime.of(2021, 7, 27, 7, 00)).selectTicket(stz3);

		ap1=new AnnualPass(ta.getAnnualPassPrice(sz3),sz3);
		ta.getPasses().add(ap1);

		cycle1=new Cycle("Cycle1");
		ta.getEvents().add(cycle1);
		cycle1.addEvent(e1);
		cycle1.addEvent(e2);
		cycle1.addEvent(e3);
		
		cp1=new CyclePass("CyclePass",10,stz3,cycle1);
		ta.getPasses().add(cp1);

		cycle2 = new Cycle("Cycle2");
		ta.getEvents().add(cycle2);
		cycle2.addEvent(e1);
	}

	@Test
	public void testSetAnnualPassPrice() {
		assertEquals(100, ta.getAnnualPassPrice(stz1),0.5);
		assertEquals(120, ta.getAnnualPassPrice(stz2),0.5);
		assertEquals(130, ta.getAnnualPassPrice(stz3),0.5);
		assertEquals(200, ta.getAnnualPassPrice(sz1),0.5);
		assertEquals(220, ta.getAnnualPassPrice(sz2),0.5);
		assertEquals(250, ta.getAnnualPassPrice(sz3),0.5);
		ta.setAnnualPassPrice(80, stz1);
		ta.setAnnualPassPrice(100, stz2);
		ta.setAnnualPassPrice(120, stz3);
		ta.setAnnualPassPrice(150, sz1);
		ta.setAnnualPassPrice(170, sz2);
		ta.setAnnualPassPrice(190, sz3);
		assertEquals(80, ta.getAnnualPassPrice(stz1),0.5);
		assertEquals(100, ta.getAnnualPassPrice(stz2),0.5);
		assertEquals(120, ta.getAnnualPassPrice(stz3),0.5);
		assertEquals(150, ta.getAnnualPassPrice(sz1),0.5);
		assertEquals(170, ta.getAnnualPassPrice(sz2),0.5);
		assertEquals(190, ta.getAnnualPassPrice(sz3),0.5);
	}

	@Test
	public void testPayTicketWithCard() {
		assertFalse(ta.payTicketWithCard(c1, e1, t1, ""));
		assertFalse(ta.payTicketWithCard(c1, e1, t1, "123456789012345"));
		assertTrue(ta.payTicketWithCard(c1, e1, t1, "1234567890123456"));
		assertTrue(c1.getTickets().contains(t1));
		assertTrue(t1.getPurchased());
	}	

	@Test
	public void testPayPassWithCard() {
		assertFalse(ta.payPassWithCard(c1, ap1, ""));
		assertFalse(ta.payPassWithCard(c1, ap1, "123456789012345"));
		assertTrue(ta.payPassWithCard(c1, ap1, "1234567890123456"));
		assertEquals(ap1.getName(),(c1.getPass(ap1.getName()).getName()));
	}

	@Test
	public void testLogIn() {
		assertTrue(ta.logIn(c1.getUsername(),c1.deCypher(c1.getPassword())));
		assertFalse(ta.logIn(c3.getUsername(),c3.deCypher(c3.getPassword())));
		assertTrue(ta.logIn(c1.getUsername(),c1.deCypher(c1.getPassword())));
		assertTrue(ta.logIn("admin","admin"));
	}

	@Test
	public void testCustomerAvailablePassesForEvent() {
		c1.addPass(ap1);
		c1.addPass(cp1);
		assertTrue((ta.customerAvailablePassesForEvent(e1, c1, t1)).contains(ap1));
		assertFalse((ta.customerAvailablePassesForEvent(e1, c2, t1)).contains(ap1));
		assertTrue((ta.customerAvailablePassesForEvent(e1, c1, t2)).contains(cp1));
		assertFalse((ta.customerAvailablePassesForEvent(e1, c2, t2)).contains(cp1));
	}

	@Test
	public void testPayWithPass() {
		c1.addPass(ap1);
		c1.addPass(cp1);
		assertTrue(ta.payWithPass(c1,ap1,e1,t1));
		assertTrue(ta.payWithPass(c1,cp1,e1,t2));
		assertTrue(c1.getTickets().contains(t1));
		assertFalse(ta.payWithPass(c2, ap1, e1, t2));
		assertFalse(ta.payWithPass(c2, cp1, e1, t1));
		assertFalse(c2.getTickets().contains(t1));
	}

	@Test
	public void testSearchEvent() {
		assertTrue(ta.searchEvent(0).contains(e3));
		assertFalse(ta.searchEvent(0).contains(e1));
		assertFalse(ta.searchEvent(0).contains(e2));
		assertTrue(ta.searchEvent(1).contains(e1));
		assertFalse(ta.searchEvent(1).contains(e2));
		assertFalse(ta.searchEvent(1).contains(e3));
		assertTrue(ta.searchEvent(2).contains(e2));
		assertFalse(ta.searchEvent(2).contains(e1));
		assertFalse(ta.searchEvent(2).contains(e3));
	}

	@Test
	public void testAddPass() {
		
		CyclePass p1 = new CyclePass("CyclePass1",20,sz3,cycle2);
		AnnualPass p2 = new AnnualPass(ta.getAnnualPassPrice(stz3),stz3);
		assertFalse(ta.getPasses().contains(p1));
		assertFalse(ta.getPasses().contains(p2));
		ta.addPass(p1);
		assertTrue(ta.getPasses().contains(p1));
		assertFalse(ta.getPasses().contains(p2));
		ta.addPass(p2);
		assertTrue(ta.getPasses().contains(p1));
		assertTrue(ta.getPasses().contains(p2));
	}

	@Test
	public void testCreateDanceEvent() {
		ta.createDanceEvent("Nutcracker", "Donatello", "Maikel", "A crazy nutcracker", "Pepe Lagarto", "Ana Bravo", "National Band",120);
		Dance d = ((Dance) ta.getEvent("Nutcracker"));
		assertTrue(ta.getEvents().contains(d));
		assertEquals(d.getTitle(),(ta.getEventStatistic(d.getTitle())).getName());
	}

	@Test
	public void testCreatePlayEvent() {
		ta.createPlayEvent("Bodas de Sangre", "Lorca", "Maikel", "A boody wedding", "Joselu, Pepe, Inma",120);
		TheaterPlay tp = ((TheaterPlay) ta.getEvent("Bodas de Sangre"));
		assertTrue(ta.getEvents().contains(tp));
		assertEquals(tp.getTitle(),(ta.getEventStatistic(tp.getTitle())).getName());
	}

	@Test
	public void testCreateConcertEvent() {
		ta.createConcertEvent("StarWars Soundtrack", "Jonh Williams", "Maikel", "A beautiful soundtrack", "Anakin, Main theme, Clone war","National orchestra",120);
		Concert c = ((Concert) ta.getEvent("StarWars Soundtrack"));
		assertTrue(ta.getEvents().contains(c));
		assertEquals(c.getTitle(),(ta.getEventStatistic(c.getTitle())).getName());
	}
	
	@Test
	public void testInitializePrices() {
		assertTrue(e2.getPrices().isEmpty());
		ta.initializePrices(e2);
		assertFalse(e2.getPrices().isEmpty());
		assertEquals(0,e2.getPrice(stz1),0.5);
		assertEquals(0,e2.getPrice(stz2),0.5);
		assertEquals(0,e2.getPrice(stz3),0.5);
		assertEquals(0,e2.getPrice(sz1),0.5);
		assertEquals(0,e2.getPrice(sz2),0.5);
		assertEquals(0,e2.getPrice(sz3),0.5);
	}

	@Test
	public void testCancelEvent() {
		assertTrue(ta.getEvents().contains(e1));
		assertEquals(e1.getTitle(),(ta.getEventStatistic(e1.getTitle())).getName());
		ta.cancelEvent(e1);
		assertFalse(ta.getEvents().contains(e1));
		assertNull(ta.getEventStatistic(e1.getTitle()));
	}

	@Test
	public void testCheckIfEventExist() {
		assertTrue(ta.checkIfEventExist(""));
		assertTrue(ta.checkIfEventExist("Swan lake"));
		assertTrue(ta.checkIfEventExist("RDR2 Soundtrack"));
		assertTrue(ta.checkIfEventExist("Romeo & Juliet"));
		assertFalse(ta.checkIfEventExist("La cucaracha"));
	}

	@Test
	public void testCheckIfCycleExist() {
		assertTrue(ta.checkIfCycleExist(""));
		assertTrue(ta.checkIfCycleExist("Cycle1"));
		assertTrue(ta.checkIfCycleExist("Cycle2"));
		assertFalse(ta.checkIfCycleExist("Ciclomotor"));
	}

	@Test
	public void testPerformance() {
		assertTrue(ta.getEvent("RDR2 Soundtrack").getPerformances().isEmpty());	
		assertFalse(ta.checkIfPerformanceExist(ta.getEvent("RDR2 Soundtrack"), LocalDateTime.of(2021, 11, 9, 11, 45)));
		ta.createPerformance(ta.getEvent("RDR2 Soundtrack"), LocalDateTime.of(2021, 11, 9, 11, 45));
		assertFalse(ta.getEvent("RDR2 Soundtrack").getPerformances().isEmpty());
		assertTrue(ta.checkIfPerformanceExist(ta.getEvent("RDR2 Soundtrack"), LocalDateTime.of(2021, 11, 9, 11, 45)));
		assertNotNull(ta.getEvent("RDR2 Soundtrack").getPerformance(LocalDateTime.of(2021, 11, 9, 11, 45)));
		ta.postponePerformace(ta.getEvent("RDR2 Soundtrack").getPerformance(LocalDateTime.of(2021, 11, 9, 11, 45)), LocalDateTime.of(2021, 11, 10, 11, 45));
		assertNull(ta.getEvent("RDR2 Soundtrack").getPerformance(LocalDateTime.of(2021, 11, 9, 11, 45)));
		ta.cancelPerformance(ta.getEvent("RDR2 Soundtrack").getPerformance(LocalDateTime.of(2021, 11, 10, 11, 45)));
		assertFalse(ta.checkIfPerformanceExist(ta.getEvent("RDR2 Soundtrack"), LocalDateTime.of(2021, 11, 10, 11, 45)));
		assertTrue(ta.getEvent("RDR2 Soundtrack").getPerformances().isEmpty());
	}


	@Test
	public void testPass() {
		assertTrue(((Customer)ta.getCustomer("Paco")).getPasses().isEmpty());
		assertNull(((Cycle)ta.getEvent("Cycle3"))); 
		ta.createCycle("Cycle3");
		assertNotNull(((Cycle)ta.getEvent("Cycle3"))); 
		ta.createDanceEvent("Swan lake", "Dostoievski", "Pepe Lagartija", "Beautiful movements", "Messi",
				"Richard Widmark", "National Band");
		assertTrue(((Cycle)ta.getEvent("Cycle3")).getEvents().isEmpty()); 
		ta.addEventToCycle( ta.getEvent("Swan lake"), ((Cycle)ta.getEvent("Cycle3")));
		assertFalse(((Cycle)ta.getEvent("Cycle3")).getEvents().isEmpty());
		ta.createCyclePass("CyclePass1", 20, ta.getZone("Sitting 1"), ((Cycle)ta.getEvent("Cycle3")));
		ta.createAnnualPass(((Customer)ta.getCustomer("Paco")), ta.getZone("Standing 2"));
	}

	@Test
	public void testCreateAnnualPass() {
		assertTrue(((Customer)ta.getCustomer("Paco")).getPasses().isEmpty());
		ta.createAnnualPass(((Customer)ta.getCustomer("Paco")), ta.getZone("Standing 1"));
		assertFalse(((Customer)ta.getCustomer("Paco")).getPasses().isEmpty());
	}

	@Test
	public void testRegister() {
		assertFalse(ta.getUsers().contains(ta.getCustomer("Miguel")));
		assertFalse(ta.logIn("Miguel", "MiguePassword"));
		assertTrue(ta.register("Miguel", "MiguePassword"));
		assertTrue(ta.getUsers().contains(ta.getCustomer("Miguel")));
		assertFalse(ta.register("Miguel", "MiguePassword"));
		assertTrue(ta.logIn("Miguel", "MiguePassword"));
	}


	@Test
	public void testTT() {
		ta.setTTB(9);
		assertEquals(ta.getTTB(), 9);

		ta.setTTP(5);
		assertEquals(ta.getTTP(), 5);

		ta.setTTB(-1);
		ta.setTTP(-1);
		assertEquals(ta.getTTB(), 9); 
		assertEquals(ta.getTTP(), 5);
		
	}

	@Test
	public void testGetEvents() {
		assertTrue(ta.getEvents().contains(e1)); 
		ta.createConcertEvent("RDR2 Soundtrack", "D'Angelo", "Pepe Lagartija", "Musical masterpiece", "Unshaken, Cruel World, Moonlight",
					"National Band");
		e2=((Concert)ta.getEvent("RDR2 Soundtrack"));
		assertTrue(ta.getEvents().contains(e2));
	}

	@Test
	public void testBooked() {
		ta.setTTP(4);
		assertNull(t2.getBookedTicket());
		assertFalse(((Customer)ta.getCustomer("Paco")).getTickets().contains(t2));
		ta.bookTicket(((Customer)ta.getCustomer("Paco")), t2);
		assertNotNull(t2.getBookedTicket());
		assertTrue(((Customer)ta.getCustomer("Paco")).getTickets().contains(t2));
		assertTrue(ta.checkBooking(((Customer)ta.getCustomer("Paco")), t2));
		ta.cancelBooking(((Customer)ta.getCustomer("Paco")), t2);
		assertNull(t2.getBookedTicket());
		assertFalse(((Customer)ta.getCustomer("Paco")).getTickets().contains(t2));

		
		ta.setTTP(0);
		ta.bookTicket(((Customer)ta.getCustomer("Paco")), t2);
		assertFalse(ta.checkBooking(((Customer)ta.getCustomer("Paco")), t2));
		assertNull(t2.getBookedTicket());
		assertFalse(((Customer)ta.getCustomer("Paco")).getTickets().contains(t2));
	}

	@Test
	public void testWaitList() {
		assertTrue(e1.getPerformance(LocalDateTime.of(2021, 7, 27, 7, 00)).getWaitList().getCustomers().isEmpty());	
		ta.suscribeToWaitList(((Customer) ta.getCustomer("Paco")),
				e1.getPerformance(LocalDateTime.of(2021, 7, 27, 7, 00)));
		assertFalse(e1.getPerformance(LocalDateTime.of(2021, 7, 27, 7, 00)).getWaitList().getCustomers()
				.contains(ta.getCustomer("Paco")));
				ta.setOccupancy(0);
		ta.suscribeToWaitList(((Customer) ta.getCustomer("Paco")),
				e1.getPerformance(LocalDateTime.of(2021, 7, 27, 7, 00)));
		assertTrue(e1.getPerformance(LocalDateTime.of(2021, 7, 27, 7, 00)).getWaitList().getCustomers()
				.contains(ta.getCustomer("Paco")));
		ta.unsuscribeOfWaitList(((Customer) ta.getCustomer("Paco")),
				e1.getPerformance(LocalDateTime.of(2021, 7, 27, 7, 00)));
		assertTrue(e1.getPerformance(LocalDateTime.of(2021, 7, 27, 7, 00)).getWaitList().getCustomers().isEmpty()); 
	}

	@Test
	public void testCheckIfZoneExist() {
		assertTrue(ta.checkIfZoneExist("Sitting 3"));
		ta.deleteZone(ta.getZone("Sitting 3"));
		assertFalse(ta.checkIfZoneExist("Sitting 3"));	
		assertTrue(ta.checkIfZoneExist("Sitting 1"));
		ta.deleteZone(ta.getZone("Sitting 1"));
		assertFalse(ta.checkIfZoneExist("Sitting 1"));
	}

	@Test
	public void testMantainSeat() {
		SittingZone z = ((SittingZone) ta.getZone("Sitting 3"));
		Seat s = z.getSeat(1, 1);	
		ta.mantainSeat(z.getName(),s.getNRow(),s.getNColumn(), LocalDate.of(2021, 10, 20), "Esta silla esta mal");
		assertEquals(s.getMSeat().getEndDate(), LocalDate.of(2021, 10, 20));
		assertEquals(s.getMSeat().getNotes(), "Esta silla esta mal");
	}

	@Test
	public void testUpdatePerformanceZoneStatistic() {
		
		ta.createPlayEvent("Romeo & Juliet", "Shakespeare", "Pepe Lagartija", "Two lovers, one destiny","Danielo, Guillerma");

		TheaterPlay e4 = ((TheaterPlay) ta.getEvent("Romeo & Juliet"));

		e1.setPrice(sz1, 4); //4
		e1.setPrice(sz2, 11); //6
		e1.setPrice(sz3, 41); //8
		e1.setPrice(stz1, 5); //10
		e1.setPrice(stz2, 5); //15
		e1.setPrice(stz3,7); //20
		e2.setPrice(sz1, 7); //4
		e2.setPrice(sz2, 8); //6
		e2.setPrice(sz3, 9); //8
		e2.setPrice(stz1, 10); //10
		e2.setPrice(stz2, 11); //15
		e2.setPrice(stz3,12); //20
		p1.getZone(fz1).setOccupancy(50); // 35/2 = 17'5
		ZoneStatistic ref = new ZoneStatistic("Reference",fz1);
		ta.createPerformance(e4,LocalDateTime.of(2021, 7, 27, 10, 00));
		ta.createPerformance(e4,LocalDateTime.of(2021, 7, 27, 11, 00));
		ta.createPerformance(ta.getEvent("Swan lake"),LocalDateTime.of(2021, 7, 27, 05, 00));
		ta.createPerformance(ta.getEvent("RDR2 Soundtrack"),LocalDateTime.of(2021, 7, 27, 05, 10));
		ta.createPerformance(ta.getEvent("Romeo & Juliet"),LocalDateTime.of(2021, 7, 27, 05, 20));
		ref.updateStatisticsFromPerformance(e1,e1.getPerformance(LocalDateTime.of(2021, 7, 27, 05, 00)),ta.getZone("Fragmented 1"));
		ta.updatePerformanceZoneStatistic(e1.getTitle(),LocalDateTime.of(2021, 7, 27, 05, 00),fz1.getName()); /// zs
		ZoneStatistic ps = ta.getZoneStatistic(fz1.getName());	
		assertEquals(ref.getOccupancy(),ps.getOccupancy(),.5);
		assertEquals(ref.getProfits(),ps.getProfits(),.5);

	}

	@Test
	public void testUpdateEventZoneStatistic() {
		
		ta.createPlayEvent("Romea & Julieto", "Shakespeare", "Pepe Lagartija", "Two lovers, one destiny","Danielo, Guillerma");

		TheaterPlay e4 = ((TheaterPlay) ta.getEvent("Romea & Julieto"));

		
		e1.setPrice(sz1, 4); //4
		e1.setPrice(sz2, 11); //6
		e1.setPrice(sz3, 41); //8
		e1.setPrice(stz1, 5); //10
		e1.setPrice(stz2, 5); //15
		e1.setPrice(stz3,7); //20
		e4.setPrice(sz1, 7); //4
		e4.setPrice(sz2, 8); //6
		e4.setPrice(sz3, 9); //8
		e4.setPrice(stz1, 10); //10
		e4.setPrice(stz2, 11); //15
		e4.setPrice(stz3,12); //20
		p1.getZone(fz1).setOccupancy(50); // 35/2 = 17'5
		ZoneStatistic ref = new ZoneStatistic("Reference",fz1);
		ref.updateStatisticsFromEvent(e1,fz1);
		
		ta.updateEventZoneStatistic(e1.getTitle(),fz1.getName()); /// zs
		ZoneStatistic ps = ta.getZoneStatistic(fz1.getName());		
		assertEquals(ref.getOccupancy(),ps.getOccupancy(),.5);
		assertEquals(ref.getProfits(),ps.getProfits(),.5);
		
	}

	@Test
	public void testUpdateZoneStatistic() {
		
		ta.createPlayEvent("Romea & Julieto", "Shakespeare", "Pepe Lagartija", "Two lovers, one destiny","Danielo, Guillerma");

		TheaterPlay e4 = ((TheaterPlay) ta.getEvent("Romea & Julieto"));
		
		e1.setPrice(sz1, 4); //4
		e1.setPrice(sz2, 11); //6
		e1.setPrice(sz3, 41); //8
		e1.setPrice(stz1, 5); //10
		e1.setPrice(stz2, 5); //15
		e1.setPrice(stz3,7); //20
		e4.setPrice(sz1, 7); //4
		e4.setPrice(sz2, 8); //6
		e4.setPrice(sz3, 9); //8
		e4.setPrice(stz1, 10); //10
		e4.setPrice(stz2, 11); //15
		e4.setPrice(stz3,12); //20
		
		p1.getZone(ta.getZone("Fragmented 1")).setOccupancy(50); // 35/2 = 17'5
		
		ArrayList<Event> events = new ArrayList<>();
		events.add(e1);
		events.add(e4);
		
		ta.createPerformance(e4,LocalDateTime.of(2021, 7, 27, 10, 00));
		ta.createPerformance(e4,LocalDateTime.of(2021, 7, 27, 11, 00));
		ta.createPerformance(ta.getEvent("Swan lake"),LocalDateTime.of(2021, 7, 27, 05, 00));
		ta.createPerformance(ta.getEvent("RDR2 Soundtrack"),LocalDateTime.of(2021, 7, 27, 05, 10));
		ta.createPerformance(ta.getEvent("Romeo & Juliet"),LocalDateTime.of(2021, 7, 27, 05, 20));
		//4.createPerformance(LocalDateTime.of(2021, 7, 27, 10, 00), zones);		
		ZoneStatistic ref = new ZoneStatistic("Fragmented 1",ta.getZone("Fragmented 1"));
		ref.updateStatistics(events,ta.getZone("Fragmented 1"));
	
		ta.updateZoneStatistic("Fragmented 1"); ///////// zs
		
		ZoneStatistic ps = ta.getZoneStatistic(fz1.getName());		
		assertEquals(ref.getOccupancy(),ps.getOccupancy(),.5);
		assertEquals(ref.getProfits(),ps.getProfits(),.5);

	}

	@Test
	public void testUpdateEventStatistic() {
		
		e1.setPrice(sz1, 4); //4
		e1.setPrice(sz2, 11); //6
		e1.setPrice(sz3, 41); //8
		e1.setPrice(stz1, 5); //10
		e1.setPrice(stz2, 5); //15
		e1.setPrice(stz3,7); //20
		
		EventStatistic ref = new EventStatistic("Reference",e1);

		p1.getZone(stz1).occupy(); //15
		p1.getZone(stz1).occupy();
		p1.getZone(stz1).occupy();
		p2.getZone(stz1).occupy();  // 5
		p2.getZone(stz2).occupy();	// 10
		p2.getZone(stz2).occupy();
		ref.updateStatistics(e1);
		
		ta.updateEventStatistic(e1.getTitle());
		EventStatistic ps = ta.getEventStatistic(e1.getTitle());
		
		assertEquals(ref.getOccupancy(),ps.getOccupancy(),.5);
		assertEquals(ref.getProfits(),ps.getProfits(),.5);
	}

	@Test
	public void testUpdatePerformanceStatistic() {
		e1.setPrice(sz1, 4);
		e1.setPrice(sz2, 11);
		e1.setPrice(sz3, 41);
		e1.setPrice(stz1, 5);
		e1.setPrice(stz2, 5);
		e1.setPrice(stz3, 7);
		
		PerformanceStatistic ref = new PerformanceStatistic("Reference",p1);
		ref.updateStatistics(e1,p1);
		
		ta.updatePerformanceStatistic(e1.getTitle(), LocalDateTime.of(2021, 7, 27, 7, 00));
		PerformanceStatistic ps = ta.getPerformanceStatistic(e1.getTitle(),LocalDateTime.of(2021, 7, 27, 7, 00));
		
		assertEquals(ref.getOccupancy(),ps.getOccupancy(),.5);
		assertEquals(ref.getProfits(),ps.getProfits(),.5);
		

	}

	@Test
	public void testSetOccupancy() {
		SittingZone z = ((SittingZone) ta.getZone("Sitting 3"));
		assertEquals(z.getNMaxPeople(), z.getNPosPeople());	
		ta.setOccupancy(50);
		assertEquals(z.getNMaxPeople(), z.getNPosPeople() * 2);
		ta.setOccupancy(100);
		assertEquals(z.getNMaxPeople(), z.getNPosPeople());
	}

	@Test
	public void testSetPrice() {
		ta.setPrice(e1.getTitle(), sz3.getName(), 10);
		ta.setPrice(e1.getTitle(), stz3.getName(), 15);
		assertEquals(e1.getPrice(sz3), 10, 0);
		assertEquals(e1.getPrice(stz3), 15, 0);
		ta.setPrice(e1.getTitle(), stz3.getName(), 10); 
		assertEquals(e1.getPrice(stz3), 10, 0);
	}

	@Test
	public void testCheckCard() {
		assertFalse(ta.checkCard(""));
		assertFalse(ta.checkCard("123456789012345"));
		assertTrue(ta.checkCard("1234567890123456"));
	}


}
