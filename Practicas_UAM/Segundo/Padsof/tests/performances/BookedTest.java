package performances;

import static org.junit.Assert.*;

import java.time.LocalDateTime;

import org.junit.Before;
import org.junit.Test;

public class BookedTest {

	Booked b1;
	Booked b2;
	LocalDateTime d1;
	LocalDateTime d2;

	@Before
	public void before(){
		d1 = LocalDateTime.of(2021,01,15,16,0,0);
		d2 = LocalDateTime.of(2021,05,15,17,0,0);
		b1 = new Booked(d1);
		b2 = new Booked(d2);
	}

	@Test
	public void testBooked() {
		assertNotNull(b1);
		assertNotNull(b2);
		assertEquals(d1,b1.getTTP());
		assertEquals(d2,b2.getTTP());
	}

	@Test
	public void testCheckOutOfTime(){
		assertFalse(b2.checkOutOfTime());
		assertTrue(b1.checkOutOfTime());
	}

}
