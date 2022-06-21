package events;

import static org.junit.Assert.*;

import org.junit.Test;
import org.junit.Before;

public class ConcertTest {

	Concert c;

	@Before
	public void before() {
		c = new Concert("RDR2 Soundtrack", "D'Angelo", "Pepe Lagartija", "Musical masterpiece", "Unshaken, Cruel World, Moonlight",
				"National Band");
	}

	@Test
	public void testConcert() {
		assertEquals("RDR2 Soundtrack",c.getTitle());
		assertEquals("D'Angelo",c.getAuthor());
		assertEquals("Pepe Lagartija",c.getDirector());
		assertEquals("Musical masterpiece",c.getDescription());
		assertEquals("Unshaken, Cruel World, Moonlight",c.getMusicPieces());
		assertEquals("National Band",c.getOrchestra());
	}

	@Test
	public void testSetMusicPieces() {
		assertEquals("Unshaken, Cruel World, Moonlight",c.getMusicPieces());
		c.setMusicPieces("Unshaken, Cruel World, Moonlight, Despacito");
		assertNotEquals("Unshaken, Cruel World, Moonlight",c.getMusicPieces());
		assertEquals("Unshaken, Cruel World, Moonlight, Despacito",c.getMusicPieces());
	}

	@Test
	public void testSetOrchestra() {
		assertEquals("National Band",c.getOrchestra());
		c.setOrchestra("The Rolling Stones");
		assertNotEquals("National Band",c.getOrchestra());
		assertEquals("The Rolling Stones",c.getOrchestra());
	}

}
