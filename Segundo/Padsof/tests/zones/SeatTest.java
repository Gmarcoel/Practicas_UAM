package zones;

import static org.junit.Assert.*;

import java.time.LocalDate;

import org.junit.Test;
import org.junit.Before;

public class SeatTest {


	Seat s1;
	Seat s2;
	Seat s3;
	MaintenanceSeat ms;

	@Before
	public void before() {
		s1 = new Seat(1, 1);
		s2 = new Seat(7, 7);
		s3 = new Seat(8, 6);
		ms = new MaintenanceSeat(LocalDate.of(2021, 7, 8), "This seat is broken");
	}

	@Test
	public void testSeat() {
		assertTrue(s1.getAvailable());
		assertFalse(s1.getOccupied());
		s1.setAvailable(false); 
		assertFalse(s1.getAvailable());
		assertFalse(s1.getOccupied());
		s1.setAvailable(true);
		s1.setOccupied(true);
		assertTrue(s1.getAvailable());
		assertEquals(s3.getNRow(), 8);
		assertEquals(s3.getNColumn(), 6);
		s1.setOccupied(false);
		s2.maintainSeat(ms.getEndDate(), ms.getNotes());
		assertTrue(s2.getOccupied());
		assertEquals(s2.getMSeat().getNotes(), ms.getNotes());
		s2.habilitateSeat();
		assertNull(s2.getMSeat());
	}


}
