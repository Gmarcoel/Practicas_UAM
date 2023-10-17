package events;

import static org.junit.Assert.*;

import org.junit.Test;
import org.junit.Before;

public class TheaterPlayTest {
	TheaterPlay t;

	@Before
	public void before() {
		t = new TheaterPlay("Romeo & Juliet", "Shakespeare", "Pepe Lagartija", "Two lovers, one destiny",
				"Danielo, Guillerma");
	}

	@Test
	public void testTheaterPlay() {
		assertEquals("Romeo & Juliet",t.getTitle());
		assertEquals("Shakespeare",t.getAuthor());
		assertEquals("Pepe Lagartija",t.getDirector());
		assertEquals("Two lovers, one destiny",t.getDescription());
		assertEquals("Danielo, Guillerma",t.getActors());

	}

	@Test
	public void testSetActors() {
		assertEquals("Danielo, Guillerma",t.getActors());
		t.setActors("Rober Wido, Scarlett");
		assertNotEquals("Danielo, Guillerma",t.getActors());
		assertEquals("Rober Wido, Scarlett",t.getActors());
	}

}
