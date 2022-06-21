package events;

import static org.junit.Assert.*;

import org.junit.Test;
import java.util.*;
import zones.*;

import org.junit.Before;

public class CyclePassTest {

	Dance d;
	TheaterPlay tp;
	Concert c;
	StandingZone z1;
	SittingZone z2;
	Cycle cycle1;
	Cycle cycle2;
	Cycle cycle3;
	CyclePass cp1;
	CyclePass cp2;
	CyclePass cp3;
	Price p1;
	Price p2;
	ArrayList<Event> ev1;
	ArrayList<Event> ev2;
	ArrayList<Event> ev3;

	@Before
	public void before() {
		d = new Dance("Swan lake", "Dostoievski", "Pepe Lagartija", "Beautiful movements", "Messi", "Richard Widmark",
				"National Band");
		tp = new TheaterPlay("Romeo & Juliet", "Shakespeare", "Pepe Lagartija", "Two lovers, one destiny",
				"Danielo, Guillerma");
		c = new Concert("RDR2 Soundtrack", "D'Angelo", "Pepe Lagartija", "Musical masterpiece",
				"Unshaken, Cruel World, Moonlight", "National Band");
		z1 = new StandingZone("standing 1", 1);
		z2 = new SittingZone("sitting 2", 2, 2);
		cycle1 = new Cycle("A");
		cycle2 = new Cycle("B");
		cycle3 = new Cycle("C");
		p1 = new Price(z1, 10);
		p2 = new Price(z2, 20);
		tp.addPrice(p1);
		tp.addPrice(p2);
		c.addPrice(p1);
		c.addPrice(p2);
		d.addPrice(p1);
		d.addPrice(p2);
		cycle3.addEvent(c);
		cycle2.addEvent(d);
		cycle2.addEvent(cycle3);
		cycle1.addEvent(tp);
		cycle1.addEvent(cycle2);
		cp1 = new CyclePass("CyclePass test1",10,z1,cycle1);
		cp2 = new CyclePass("CyclePass test2",10,z1,cycle2);
		cp3 = new CyclePass("CyclePass test3",10,z2,cycle3);
	}

	@Test
	public void testCyclePass() {
		assertNotNull(cp1);
		assertNotNull(cp2);
		assertNotNull(cp3);
		assertEquals("CyclePass test1",cp1.getName());
		assertEquals("CyclePass test2",cp2.getName());
		assertEquals("CyclePass test3",cp3.getName());
		assertEquals(10,cp1.getDiscountPercentage());
		assertEquals(10,cp2.getDiscountPercentage());
		assertEquals(10,cp3.getDiscountPercentage());
		assertEquals(z1,cp1.getZone());
		assertEquals(z1,cp2.getZone());
		assertEquals(z2,cp3.getZone());
		assertEquals(cycle1,cp1.getCycle());
		assertEquals(cycle2,cp2.getCycle());
		assertEquals(cycle3,cp3.getCycle());
	}

	@Test
	public void testSetName() {
		assertEquals("CyclePass test1",cp1.getName());
		cp1.setName("CyclePass test1.1");
		assertNotEquals("CyclePass test1",cp1.getName());
		assertEquals("CyclePass test1.1",cp1.getName());
		assertEquals("CyclePass test2",cp2.getName());
		cp2.setName("CyclePass test2.1");
		assertNotEquals("CyclePass test2",cp2.getName());
		assertEquals("CyclePass test2.1",cp2.getName());
		assertEquals("CyclePass test3",cp3.getName());
		cp3.setName("CyclePass test3.1");
		assertNotEquals("CyclePass test3",cp3.getName());
		assertEquals("CyclePass test3.1",cp3.getName());
	}

	@Test
	public void testSetDiscountPercentage() {
		assertEquals(10,cp1.getDiscountPercentage());
		cp1.setDiscountPercentage(20);
		assertNotEquals(10,cp1.getName());
		assertEquals(20,cp1.getDiscountPercentage());
		assertEquals(10,cp2.getDiscountPercentage());
		cp2.setDiscountPercentage(20);
		assertNotEquals(10,cp2.getDiscountPercentage());
		assertEquals(20,cp2.getDiscountPercentage());
		assertEquals(10,cp3.getDiscountPercentage());
		cp3.setDiscountPercentage(20);
		assertNotEquals(10,cp3.getDiscountPercentage());
		assertEquals(20,cp3.getDiscountPercentage());
	}

	@Test
	public void testSetCycle() {
		assertEquals(cycle1,cp1.getCycle());
		cp1.setCycle(cycle2);
		assertNotEquals(cycle1,cp1.getCycle());
		assertEquals(cycle2,cp1.getCycle());
	}

	@Test
	public void testSetCanGoToList() {
		assertTrue(cp1.getCanGoToList().contains(d));
		assertTrue(cp1.getCanGoToList().contains(tp));
		assertTrue(cp1.getCanGoToList().contains(c));
		assertTrue(cp2.getCanGoToList().contains(d));
		assertTrue(cp2.getCanGoToList().contains(c));
		assertTrue(cp3.getCanGoToList().contains(c));
	}

	@Test
	public void testRemoveAttendedEvent() {
		assertTrue(cp1.getCanGoToList().contains(d));
		assertTrue(cp1.getCanGoToList().contains(tp));
		assertTrue(cp1.getCanGoToList().contains(c));
		assertTrue(cp1.getAlreadyAttendedList().isEmpty());
		cp1.addAlreadyAttended(d);
		assertFalse(cp1.getCanGoToList().contains(d));
		assertTrue(cp1.getCanGoToList().contains(tp));
		assertTrue(cp1.getCanGoToList().contains(c));
		assertTrue(cp1.getAlreadyAttendedList().contains(d));
		assertFalse(cp1.getAlreadyAttendedList().contains(tp));
		assertFalse(cp1.getAlreadyAttendedList().contains(c));
		cp1.addAlreadyAttended(tp);
		assertFalse(cp1.getCanGoToList().contains(d));
		assertFalse(cp1.getCanGoToList().contains(tp));
		assertTrue(cp1.getCanGoToList().contains(c));
		assertTrue(cp1.getAlreadyAttendedList().contains(d));
		assertTrue(cp1.getAlreadyAttendedList().contains(tp));
		assertFalse(cp1.getAlreadyAttendedList().contains(c));
		cp1.addAlreadyAttended(c);
		assertTrue(cp1.getCanGoToList().isEmpty());
		assertTrue(cp1.getAlreadyAttendedList().contains(d));
		assertTrue(cp1.getAlreadyAttendedList().contains(tp));
		assertTrue(cp1.getAlreadyAttendedList().contains(c));
	}

	@Test
	public void testCalculateDiscountedPrice() {
		assertEquals(27, cp1.calculateDiscountedPrice(),0.5);
		assertEquals(18,cp2.calculateDiscountedPrice(),0.5);
		assertEquals(18,cp3.calculateDiscountedPrice(),0.5);
	}

}
