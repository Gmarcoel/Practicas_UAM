package zones;

import static org.junit.Assert.*;

import java.util.ArrayList;

import org.junit.Test;
import org.junit.Before;

public class FragmentedZoneTest {

	FragmentedZone fz1;
	FragmentedZone fz2;
	FragmentedZone fz3;
	StandingZone stz1;
	StandingZone stz2;
	SittingZone sz1;
	SittingZone sz2;

	@Before
	public void before() {
		stz1=new StandingZone("Standing 1", 20);
		stz2=new StandingZone("Standing 2", 10);
		sz1=new SittingZone("Sitting 1", 4, 4);
		sz2=new SittingZone("Sitting 2", 10, 2);
		fz1=new FragmentedZone("Fragmented 1");
		fz2=new FragmentedZone("Fragmented 1.1");
		fz1.addSubzone(fz2);
		fz1.addSubzone(stz1);
		fz2.addSubzone(sz1);
		fz3=new FragmentedZone("Fragmented 2");
		fz3.addSubzone(sz2);
		fz3.addSubzone(stz2);

	}

	@Test
	public void testFragmentedZone() {
		ArrayList<Zone> zones1;
		zones1 = new ArrayList<Zone>();
		zones1.add(fz2);
		zones1.add(stz1);
		
		ArrayList<Zone> zones2;
		zones2 = new ArrayList<Zone>();
		zones2.add(sz1);

		ArrayList<Zone> zones3;
		zones3 = new ArrayList<Zone>();
		zones3.add(sz2);
		zones3.add(stz2);

		assertEquals(fz1.getSubZones(), zones1);
		assertEquals(fz2.getSubZones(), zones2);
		assertEquals(fz3.getSubZones(), zones3);

		sz1.occupy(sz1.getSeat(0, 2));
		assertFalse(fz1.isOccupied(sz1, sz1.getSeat(0, 3)));
		assertTrue(fz1.isOccupied(sz1, sz1.getSeat(0, 2)));
		assertFalse(fz1.isOccupied(stz1));
		stz1.setNPeople(20);
		assertTrue(fz1.isOccupied(stz1));

		sz1.free(sz1.getSeat(0, 2));
		
	}
	//fz1.addSubzone(fz2);
	//fz1.addSubzone(stz1);
	//fz2.addSubzone(sz1);
	@Test
	public void testOccupancy() {
		assertEquals(fz2.getOccupancy(),100);
		assertEquals(stz1.getOccupancy(),100);
		assertEquals(sz1.getOccupancy(),100);
		assertEquals(fz1.getOccupancy(), 100);
		fz1.setOccupancy(50);
		assertEquals(fz1.getOccupancy(),50,0);
		sz1.setOccupancy(75);
		assertEquals(fz1.getOccupancy(),61,0); 
	}


	@Test
	public void testClone() {
		FragmentedZone fz4 = (FragmentedZone)fz1.cloneZone();
		assertEquals(fz1.getName(), fz4.getName());
		int i = 0;
		for (Zone z :fz1.getSubZones()) {
			assertEquals(z.getName(),(fz4.getSubZones().get(i)).getName());
			i++;
		}
		assertNotSame(fz1, fz4);
	}

	


}
