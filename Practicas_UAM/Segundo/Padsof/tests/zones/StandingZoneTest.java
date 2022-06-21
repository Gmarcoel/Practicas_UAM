package zones;

import static org.junit.Assert.*;

import org.junit.Test;
import org.junit.Before;

public class StandingZoneTest {

	StandingZone sz1;
	StandingZone sz2;
	StandingZone sz3;

	@Before
	public void before() {
		sz1 = new StandingZone("standing 1", 1);
		sz2 = new StandingZone("standing 2", 2);
		sz3 = new StandingZone("standing 3", 3);
	}

	@Test
	public void testStandingZone() {
		assertFalse(sz1.isOccupied());
		assertFalse(sz2.isOccupied());
		assertFalse(sz3.isOccupied());
		sz1.occupy();
		sz2.occupy();
		sz3.occupy();
		assertTrue(sz1.isOccupied());
		assertFalse(sz2.isOccupied());
		assertFalse(sz3.isOccupied());
		sz2.occupy();
		sz3.occupy();
		assertTrue(sz2.isOccupied());
		assertFalse(sz3.isOccupied());
		sz3.occupy();
		assertTrue(sz3.isOccupied());
		sz3.occupy();
		assertEquals(sz3.getNPeople(), 3);
	}

	@Test
	public void testGetOccupancy() {
		assertEquals(sz1.getOccupancy(), 100, 0);
		assertEquals(sz2.getOccupancy(), 100, 0);
		sz2.setOccupancy(50);
		assertEquals(sz2.getOccupancy(), 50, 0);
		sz2.occupy();
	}

	@Test
	public void testGetNMaxPeople() {
		assertEquals(sz1.getNMaxPeople(), 1);
		assertEquals(sz2.getNMaxPeople(), 2);
		assertEquals(sz3.getNMaxPeople(), 3);
		
	}
	

	@Test
	public void testGetNPeople() {
		assertEquals(sz1.getNPeople(), 0);
		sz1.occupy();
		assertEquals(sz1.getNPeople(), 1);
	}
	
	
	
	@Test
	public void testGetNPosPeople() {
		assertEquals(sz3.getNPosPeople(),3);
		sz3.setOccupancy(34);
		assertEquals(sz3.getNPosPeople(),1);
		sz3.setOccupancy(67);
		assertEquals(sz3.getNPosPeople(),2);
	}

	@Test
	public void testSetNMaxPeople() {
		assertEquals(sz1.getNMaxPeople(), 1);
		sz1.setNMaxPeople(10);
		assertEquals(sz1.getNMaxPeople(), 10);
	}

	@Test
	public void testSetNPeople() {
		sz3.setNPeople(2);
		assertEquals(sz3.getNPeople(), 2);
		sz1.setNPeople(8);
		assertEquals(sz1.getNPeople(), 0);
		sz3.setNPeople(8);
		assertEquals(sz3.getNPeople(), 2);
	}

	
	@Test
	public void testClone() {
		StandingZone sz4 = (StandingZone)sz1.cloneZone();
		assertEquals(sz1.getName(), sz4.getName());
		assertNotSame(sz1, sz4);
	}

}
