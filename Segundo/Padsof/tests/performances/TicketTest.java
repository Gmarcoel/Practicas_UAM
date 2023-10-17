package performances;

import zones.*;
import events.*;


import java.util.*;
import java.time.*;
import static org.junit.Assert.*;

import org.junit.Test;
import org.junit.Before;

public class TicketTest {

	SittingZone sz;
	StandingZone stz;
	ArrayList<Zone> zones;
	TheaterPlay e;
	Performance p;
	Ticket t;
	Ticket t2;

	@Before
	public void before(){
		sz = new SittingZone("Sitting1", 6, 6);
		stz = new StandingZone("Standing1", 20);
		sz.occupy(sz.getSeat(1, 5));
		stz.occupy();
		zones = new ArrayList<Zone>();
		zones.add(sz);
		zones.add(stz);
		e = new TheaterPlay("Romeo & Juliet", "Shakespeare", "Francois", "Two crazy guys", "Guille, Dani");
		p = new Performance(LocalDateTime.of(2021, 07, 12, 10, 30), zones, e);
		t = new Ticket(sz, sz.getSeat(1, 5), p);
		t2 = new Ticket(stz, p);
	}

	@Test
	public void testGetZone() {
		assertEquals(t.getZone(), sz);
		assertEquals(t2.getZone(), stz);
	}


	@Test
	public void testGetSeat() {
		assertEquals(t.getSeat(), sz.getSeat(1, 5));
		assertEquals(t2.getSeat(), null);
	}

	@Test
	public void testGetPerformance() {
		assertEquals(t.getPerformance(), p);
		assertEquals(t2.getPerformance(), p);
	}

	@Test
	public void testSetPurchased() {
		sz.free(sz.getSeat(1, 5));
		assertFalse(t.getSeat().getOccupied());
		assertFalse(t.getPurchased());
		t.setPurchased(true);
		assertTrue(t.getPurchased());
		assertTrue(t.getSeat().getOccupied());

		
		((StandingZone)t2.getZone()).free();
		assertEquals(t2.getZone().getAttendees(), 0);
		assertFalse(t2.getPurchased());
		t2.setPurchased(true);
		assertTrue(t2.getPurchased());
		assertEquals(t2.getZone().getAttendees(), 1); 

	}

	@Test
	public void testSetBookedTicket() {
		((SittingZone)t.getZone()).free(t.getSeat());
		((StandingZone)t2.getZone()).free();

		assertFalse(t.getSeat().getOccupied()); 

		t.setBookedTicket(new Booked(LocalDateTime.of(2021, 6, 11, 3, 30).plusHours(5)));
		assertEquals(t.getBookedTicket().getTTP().getHour(), 8);
		assertEquals(t.getBookedTicket().getTTP().getMinute(), 30);
		
		assertTrue(t.getSeat().getOccupied()); 
		t.setPurchased(true);
		assertTrue(t.getSeat().getOccupied());

		
		assertEquals(t2.getZone().getAttendees(), 0);
		t2.setPurchased(true);
		assertEquals(t2.getZone().getAttendees(), 1);


	}

	@Test
	public void testFreeTicket() {
		assertTrue(t.getSeat().getOccupied());
		t.freeTicket();
		assertFalse(t.getSeat().getOccupied());

		assertEquals(t2.getZone().getAttendees(), 1); 
		t2.freeTicket();
		assertEquals(t2.getZone().getAttendees(), 0);
	}

	@Test
	public void testGenerateTicketPDF() {
		t.generateTicketPDF();
	}

}
