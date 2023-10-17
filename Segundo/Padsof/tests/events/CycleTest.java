package events;

import static org.junit.Assert.*;

import org.junit.Test;

import zones.*;

import org.junit.Before;

public class CycleTest {

	Dance d;
	TheaterPlay tp;
	Concert c;
	StandingZone z1;
	SittingZone z2;
	Cycle cycle1;
	Cycle cycle2;
	Cycle cycle3;
	Price p1;
	Price p2;

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
	}

	@Test
	public void testCycle() {
		assertEquals("A", cycle1.getTitle());
		assertEquals("B", cycle2.getTitle());
		assertEquals("C", cycle3.getTitle());
		assertNotNull(cycle1.getEvents());
		assertNotNull(cycle2.getEvents());
		assertNotNull(cycle3.getEvents());
		assertTrue(cycle1.getEvents().isEmpty());
		assertTrue(cycle2.getEvents().isEmpty());
		assertTrue(cycle3.getEvents().isEmpty());
	}

	@Test
	public void testAddEvent() {
		assertTrue(cycle1.getEvents().isEmpty());
		cycle1.addEvent(c);
		assertFalse(cycle1.getEvents().isEmpty());
		assertTrue(cycle1.getEvents().contains(c));
		assertTrue(cycle2.getEvents().isEmpty());
		cycle2.addEvent(d);
		assertFalse(cycle2.getEvents().isEmpty());
		assertTrue(cycle2.getEvents().contains(d));
		assertTrue(cycle3.getEvents().isEmpty());
		cycle3.addEvent(tp);
		assertFalse(cycle3.getEvents().isEmpty());
		assertTrue(cycle3.getEvents().contains(tp));
		cycle2.addEvent(cycle3);
		assertTrue(cycle2.getEvents().contains(cycle3));
		cycle1.addEvent(cycle2);
		assertFalse(cycle1.getEvents().contains(cycle3));
	}

	@Test
	public void testGetEvents() {
		assertTrue(cycle1.getEvents().isEmpty());
		cycle1.addEvent(c);
		assertFalse(cycle1.getEvents().isEmpty());
		assertTrue(cycle1.getEvents().contains(c));
		assertTrue(cycle2.getEvents().isEmpty());
		cycle2.addEvent(d);
		assertFalse(cycle2.getEvents().isEmpty());
		assertTrue(cycle2.getEvents().contains(d));
		assertTrue(cycle3.getEvents().isEmpty());
		cycle3.addEvent(tp);
		assertFalse(cycle3.getEvents().isEmpty());
		assertTrue(cycle3.getEvents().contains(tp));
		cycle2.addEvent(cycle3);
		assertTrue(cycle2.getEvents().contains(cycle3));
		cycle1.addEvent(cycle2);
		assertFalse(cycle1.getEvents().contains(cycle3));

		assertFalse(cycle1.getEvents().isEmpty());
		assertFalse(cycle2.getEvents().isEmpty());
		assertFalse(cycle3.getEvents().isEmpty());
		assertTrue(cycle1.getEvents().contains(c));
		assertTrue(cycle1.getEvents().contains(cycle2));
		assertFalse(cycle1.getEvents().contains(d));
		assertFalse(cycle1.getEvents().contains(cycle3));
		assertFalse(cycle1.getEvents().contains(tp));
		assertTrue(cycle2.getEvents().contains(d));
		assertTrue(cycle2.getEvents().contains(cycle3));
		assertFalse(cycle2.getEvents().contains(tp));
		assertTrue(cycle3.getEvents().contains(tp));
	}

	@Test
	public void testCalculateSumPrice() {
		assertTrue(cycle1.getEvents().isEmpty());
		cycle1.addEvent(c);
		assertFalse(cycle1.getEvents().isEmpty());
		assertTrue(cycle1.getEvents().contains(c));
		assertTrue(cycle2.getEvents().isEmpty());
		cycle2.addEvent(d);
		assertFalse(cycle2.getEvents().isEmpty());
		assertTrue(cycle2.getEvents().contains(d));
		assertTrue(cycle3.getEvents().isEmpty());
		cycle3.addEvent(tp);
		assertFalse(cycle3.getEvents().isEmpty());
		assertTrue(cycle3.getEvents().contains(tp));
		cycle2.addEvent(cycle3);
		assertTrue(cycle2.getEvents().contains(cycle3));
		cycle1.addEvent(cycle2);
		assertFalse(cycle1.getEvents().contains(cycle3));

		assertEquals(10, cycle3.calculateSumPrice(z1), 0.5);
		assertEquals(20, cycle3.calculateSumPrice(z2), 0.5);
		assertEquals(20, cycle2.calculateSumPrice(z1), 0.5);
		assertEquals(40, cycle2.calculateSumPrice(z2), 0.5);
		assertEquals(30, cycle1.calculateSumPrice(z1), 0.5);
		assertEquals(60, cycle1.calculateSumPrice(z2), 0.5);
	}

}
