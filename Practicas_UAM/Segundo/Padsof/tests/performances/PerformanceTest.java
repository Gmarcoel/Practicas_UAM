package performances;

import zones.*;
import events.*;


import java.util.*;
import java.time.*;

import static org.junit.Assert.*;

import org.junit.Test;
import org.junit.Before;

public class PerformanceTest {

	SittingZone sz;
	StandingZone stz;
	ArrayList<Zone> zones1;
	TheaterPlay e;
	Performance p;
	Performance p2;

	
	SittingZone sz2;
	SittingZone sz3;
	FragmentedZone fz;
	ArrayList<Zone> zones2;
	Dance e2;
	Performance p3;


	@Before
	public void before(){
		sz = new SittingZone("Sitting1", 6, 6);
		stz = new StandingZone("Standing1", 20);

		sz2 = new SittingZone("Sitting2", 4, 6);
		sz3 = new SittingZone("Sitting3", 7, 9);

		fz = new FragmentedZone("Fragmented1");
		
		zones1 = new ArrayList<Zone>();
		zones1.add(sz);
		zones1.add(stz);
		
		zones2 = new ArrayList<Zone>();
		fz.addSubzone(sz2);
		zones1.add(fz);
		zones1.add(sz3);

		e = new TheaterPlay("Romeo & Juliet", "Shakespeare", "Francois", "Two crazy guys", "Guille, Dani");
		e2 = new Dance("El rey leon", "Blas Canto", "Alemanois", "Two crazy lions", "ConductorGuy", "Dancer 1, Rafa Mendez", "orchestra sinfonica siciliana");

		p = new Performance(LocalDateTime.of(2021, 7, 27, 7, 00), zones1, e);
		p2 = new Performance(LocalDateTime.of(2021, 11, 12, 10, 30), zones1, e);

		p3 = new Performance(LocalDateTime.of(2022, 1, 1, 9, 15), zones2, e2);

	}

// 79 89 109

	@Test
	public final void testPostponePerformance() {
		assertEquals(p.getDate(), LocalDateTime.of(2021, 7, 27, 7, 00));
		p.postponePerformance(LocalDateTime.of(2021, 8, 15, 7, 15));
		assertEquals(p.getDate(), LocalDateTime.of(2021, 8, 15, 7, 15));
		p.postponePerformance(LocalDateTime.of(2021, 7, 15, 7, 15));
		assertEquals(p.getDate(), LocalDateTime.of(2021, 8, 15, 7, 15));
	}

	@Test
	public final void testCheckOccupiedZoneSeat() {
		assertFalse(p.checkOccupied(p.getZone(sz), ((SittingZone)p.getZone(sz)).getSeat(3, 2)));
		((SittingZone)p.getZone(sz)).getSeat(3, 2).setOccupied(true);
		assertTrue(p.checkOccupied(p.getZone(sz), ((SittingZone)p.getZone(sz)).getSeat(3, 2)));
		
		assertFalse(p2.checkOccupied(p2.getZone(sz2), ((SittingZone)((FragmentedZone)p.getZone(fz)).getSubZone(sz2.getName())).getSeat(1, 1)));
		((SittingZone)((FragmentedZone)p.getZone(fz)).getSubZone(sz2.getName())).getSeat(1, 1).setOccupied(true);
		assertTrue(p.checkOccupied(p2.getZone(sz2), ((SittingZone)((FragmentedZone)p.getZone(fz)).getSubZone(sz2.getName())).getSeat(1, 1)));
	}

	@Test
	public final void testCheckOccupiedZone() {
		((StandingZone)p.getZone(stz)).setNPeople(19);;
		assertFalse(p.checkOccupied(p.getZone(stz)));
		((StandingZone)p.getZone(stz)).occupy();
		assertTrue(p.checkOccupied(p.getZone(stz)));
	}

	@Test
	public final void testSelectTicketZoneSeat() {
		Ticket t = p.selectTicket(p.getZone(sz), ((SittingZone)p.getZone(sz)).getSeat(2, 2));
		assertNull(t.getBookedTicket());
		assertEquals(t.getSeat(), ((SittingZone)p.getZone(sz)).getSeat(2, 2));
		assertFalse(((SittingZone)p.getZone(sz)).getSeat(2, 2).getOccupied());
		t.setBookedTicket(new Booked(LocalDateTime.now().plusHours(20)));
		assertTrue(((SittingZone)p.getZone(sz)).getSeat(2, 2).getOccupied());
		p.cancelPerformanceTicket(t);
		assertFalse(((SittingZone)p.getZone(sz)).getSeat(2, 2).getOccupied());
	}


	@Test
	public final void testSelectTicketZone() {
		Ticket t = p.selectTicket(p.getZone(stz));
		assertNull(t.getBookedTicket());
		assertEquals(((StandingZone)p.getZone(stz)).getNPeople(), 0);
		t.setBookedTicket(new Booked(LocalDateTime.now().plusHours(20)));
		assertEquals(((StandingZone)p.getZone(stz)).getNPeople(), 1);
		p.cancelPerformanceTicket(t);
		assertEquals(((StandingZone)p.getZone(stz)).getNPeople(), 0);
	}

	@Test
	public final void testGetEvent() {
		assertEquals(p.getEvent(), e);
		assertEquals(p2.getEvent(), e);
		assertEquals(p3.getEvent(), e2);
	}

}
