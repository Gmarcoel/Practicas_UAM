package events;

import static org.junit.Assert.*;

import org.junit.Test;
import org.junit.Before;

public class DanceTest {

	Dance d;

	@Before
	public void before() {
		d = new Dance("Swan lake", "Dostoievski", "Pepe Lagartija", "Beautiful movements", "Messi", "Richard Widmark",
				"National Band");
	}

	@Test
	public void testDance() {
		assertEquals("Swan lake",d.getTitle());
		assertEquals("Dostoievski",d.getAuthor());
		assertEquals("Pepe Lagartija",d.getDirector());
		assertEquals("Beautiful movements",d.getDescription());
		assertEquals("Messi",d.getConductor());
		assertEquals("Richard Widmark",d.getDancer());
		assertEquals("National Band",d.getOrchestra());
	}

	@Test
	public void testSetConductor() {
		assertEquals("Messi",d.getConductor());
		d.setConductor("Danielo Varela");
		assertNotEquals("Messi",d.getConductor());
		assertEquals("Danielo Varela",d.getConductor());
	}

	@Test
	public void testSetDancer() {
		assertEquals("Richard Widmark",d.getDancer());
		d.setDancer("Raul Gonzalez");
		assertNotEquals("Richard Widmark",d.getDancer());
		assertEquals("Raul Gonzalez",d.getDancer());
	}

	@Test
	public void testSetOrchestra() {
		assertEquals("National Band",d.getOrchestra());
		d.setOrchestra("The Rolling Stones");
		assertNotEquals("National Band",d.getOrchestra());
		assertEquals("The Rolling Stones",d.getOrchestra());
	}

}
