package zones;

import static org.junit.Assert.*;

import org.junit.Test;
import org.junit.Before;

public class SittingZoneTest {

	SittingZone sz1;
	SittingZone sz2;
	SittingZone sz3;
	SittingZone sz4;
	Seat[][] array1;

	@Before
	public void before() {
		sz1 = new SittingZone("sitting 1", 1, 1);
		sz2 = new SittingZone("sitting 2", 2, 1);
		sz3 = new SittingZone("sitting 3", 1, 2);
		sz4 = new SittingZone("sitting 4", 2, 2);

		array1 = new Seat[sz4.getNRows()][sz4.getNColumns()];

		
		array1[0][0] = new Seat(0,0);
		array1[0][1] = new Seat(0,1);
		array1[1][0] = new Seat(1,0);
		array1[1][1] = new Seat(1,1);
	}

	@Test
	public void testSittingZone() {

		assertEquals(sz4.getSeat(0, 0).getNRow(), array1[0][0].getNRow());
		assertEquals(sz4.getSeat(0, 0).getNColumn(), array1[0][0].getNColumn());
		assertEquals(sz4.getSeat(1, 0).getNRow(), array1[1][0].getNRow());
		assertEquals(sz4.getSeat(1, 0).getNColumn(), array1[1][0].getNColumn());
		assertEquals(sz4.getSeat(0, 1).getNRow(), array1[0][1].getNRow());
		assertEquals(sz4.getSeat(0, 1).getNColumn(), array1[0][1].getNColumn());
		assertEquals(sz4.getSeat(1, 1).getNRow(), array1[1][1].getNRow());
		assertEquals(sz4.getSeat(1, 1).getNColumn(), array1[1][1].getNColumn());
		
		array1[0][0].setAvailable(false);
		array1[1][0].setAvailable(false);

		sz4.setOccupancy(50);

		assertEquals(sz4.getSeat(0, 0).getAvailable(), array1[0][0].getAvailable()); //
		assertEquals(sz4.getSeat(1, 0).getAvailable(), array1[1][0].getAvailable());
		assertEquals(sz4.getSeat(0, 1).getAvailable(), array1[0][1].getAvailable());
		assertEquals(sz4.getSeat(1, 1).getAvailable(), array1[1][1].getAvailable());

		
		array1[0][0].setAvailable(true);
		array1[1][0].setAvailable(true);

		sz4.resetSeatsAvailability();

		
		assertEquals(sz4.getSeat(0, 0).getAvailable(), array1[0][0].getAvailable());
		assertEquals(sz4.getSeat(1, 0).getAvailable(), array1[1][0].getAvailable());
		assertEquals(sz4.getSeat(0, 1).getAvailable(), array1[0][1].getAvailable());
		assertEquals(sz4.getSeat(1, 1).getAvailable(), array1[1][1].getAvailable());
	}


	@Test
	public void testGetNRows() {
		assertEquals(sz1.getNRows(), 1);
		assertEquals(sz2.getNRows(), 2);
		assertEquals(sz3.getNRows(), 1);
		assertEquals(sz4.getNRows(), 2);
	}

	@Test
	public void testGetNColumns() {
		assertEquals(sz1.getNColumns(), 1);
		assertEquals(sz2.getNColumns(), 1);
		assertEquals(sz3.getNColumns(), 2);
		assertEquals(sz4.getNColumns(), 2);
	}

	@Test
	public void testSetNRows() {
		assertEquals(sz1.getNRows(), 1);
		sz1.setNRows(5);
		assertEquals(sz1.getNRows(), 5);
	}

	@Test
	public void testSetNColumns() {
		assertEquals(sz1.getNColumns(), 1);
		sz1.setNColumns(5);
		assertEquals(sz1.getNColumns(), 5);
	}

	@Test
	public void testOccupy() {
		assertFalse(sz4.isOccupied(sz4.getSeat(1, 1)));
		sz4.occupy(sz4.getSeat(1, 1));
		assertTrue(sz4.isOccupied(sz4.getSeat(1, 1)));
	}
	
	@Test
	public void testNMaxPeople() {
		assertEquals(sz4.getNMaxPeople(),4);
	}

	@Test
	public void testNPosPeople() {

		assertEquals(sz4.getNPosPeople(), 4, 0);
		sz4.setOccupancy(50);
		assertEquals(sz4.getNPosPeople(), 2, 0);
	}
	
	@Test
	public void testClone() {
		SittingZone sz5 = (SittingZone)sz1.cloneZone();
		assertEquals(sz1.getName(), sz5.getName());
		assertNotSame(sz1, sz5);
	}
}
