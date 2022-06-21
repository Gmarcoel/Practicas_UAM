package users;

import static org.junit.Assert.*;

import events.*;
import zones.*;
import performances.*;

import java.util.ArrayList;
import java.time.*;

import org.junit.Test;
import org.junit.Before;

public class CustomerTest {

	Customer c1;
	Customer c2;
	Customer c3;
	CyclePass p1;
	Cycle cy1;
	AnnualPass p2;
	StandingZone sz;
	SittingZone sz2;
	Ticket t1;
	Ticket t2;
	Ticket t3;
	Seat st1;
	Seat st2;
	Performance p;
	Event e;
	ArrayList<Zone> zones;

	@Before
	public void before() {
		c1 = new Customer("Paco", "pacopassword");
		c2 = new Customer("Pepe Lagartija", "pepeLagarto");
		c3 = new Customer("Miguel", "contrasena");
		sz = new StandingZone("Standing 1", 30);
		zones = new ArrayList<Zone>();
		zones.add(sz);
		e = new TheaterPlay("Romeo & Juliet", "Shakespeare", "Francois", "Two crazy guys", "Guille, Dani");
		p = new Performance(LocalDateTime.now(), zones, e);
	}

	@Test
	public void testGetTickets() {
		st1 = new Seat(4, 7);
		st2 = new Seat(1, 2);
		t1 = new Ticket(sz, p);
		t2 = new Ticket(sz2, st1, p);
		t3 = new Ticket(sz2, st2, p);
		ArrayList<Ticket> array1 = new ArrayList<>();
		ArrayList<Ticket> array2 = new ArrayList<>();
		array1.add(t1);
		array1.add(t2);
		array2.add(t3);
		c1.addTicket(t1);
		c1.addTicket(t2);
		c2.addTicket(t3);

		assertEquals(c1.getTickets(), array1);
		assertEquals(c2.getTickets(), array2);
		assertTrue(c3.getTickets().isEmpty());
	}

	@Test
	public void testGetPasses() {
		cy1 = new Cycle("cycle 1");
		p1 = new CyclePass("18th century", 30, sz, cy1);
		p2 = new AnnualPass(200, sz);
		c1.addPass(p1);
		c1.addPass(p2);
		c2.addPass(p2);
		ArrayList<Pass> array1 = new ArrayList<>();
		ArrayList<Pass> array2 = new ArrayList<>();
		array1.add(p1);
		array1.add(p2);
		array2.add(p2);

		assertEquals(c1.getPasses(), array1);
		assertEquals(c2.getPasses(), array2);
		assertTrue(c3.getPasses().isEmpty());
	}

	@Test
	public void testRemovePass() {
		cy1 = new Cycle("cycle 1");
		p1 = new CyclePass("18th century", 30, sz, cy1);
		p2 = new AnnualPass(200, sz);
		c1.addPass(p1);
		c1.addPass(p2);
		ArrayList<Pass> array1 = new ArrayList<>();
		ArrayList<Pass> array2 = new ArrayList<>();
		array1.add(p1);
		array1.add(p2);
		array2.add(p1);

		assertEquals(c1.getPasses(), array1);
		c1.removePass(p2);
		assertEquals(c1.getPasses(), array2);
		c1.removePass(p1);
		assertTrue(c3.getPasses().isEmpty());
	}

	@Test
	public void testRemoveTicket() {
		st1 = new Seat(4, 7);
		t1 = new Ticket(sz, p);
		t2 = new Ticket(sz2, st1, p);
		ArrayList<Ticket> array1 = new ArrayList<>();
		ArrayList<Ticket> array2 = new ArrayList<>();
		array1.add(t1);
		array1.add(t2);
		array2.add(t1);
		c1.addTicket(t1);
		c1.addTicket(t2);

		assertEquals(c1.getTickets(), array1);
		c1.removeTicket(t2);
		assertEquals(c1.getTickets(), array2);
		c1.removeTicket(t1);
		assertTrue(c1.getTickets().isEmpty());
	}

	@Test
	public void testAddPass() {
		cy1 = new Cycle("cycle 1");
		p1 = new CyclePass("18th century", 30, sz, cy1);
		p2 = new AnnualPass(200, sz);
		ArrayList<Pass> array1 = new ArrayList<>();
		ArrayList<Pass> array2 = new ArrayList<>();
		array1.add(p1);
		array2.add(p1);
		array2.add(p2);
		assertTrue(c1.getPasses().isEmpty());
		c1.addPass(p1);
		assertEquals(c1.getPasses(), array1);
		c1.addPass(p2);
		assertEquals(c1.getPasses(), array2);
	}

	@Test
	public void testAddTicket() {
		st1 = new Seat(4, 7);
		st2 = new Seat(1, 2);
		t1 = new Ticket(sz, p);
		t2 = new Ticket(sz2, st1, p);
		t3 = new Ticket(sz2, st2, p);
		ArrayList<Ticket> array1 = new ArrayList<>();
		ArrayList<Ticket> array2 = new ArrayList<>();
		ArrayList<Ticket> array3 = new ArrayList<>();
		array1.add(t1);
		array2.add(t1);
		array2.add(t2);
		array3.add(t1);
		array3.add(t2);
		array3.add(t3);
		assertTrue(c1.getTickets().isEmpty());
		c1.addTicket(t1);
		assertEquals(c1.getTickets(), array1);
		c1.addTicket(t2);
		assertEquals(c1.getTickets(), array2);
		c1.addTicket(t3);
		assertEquals(c1.getTickets(), array3);
	}

}
