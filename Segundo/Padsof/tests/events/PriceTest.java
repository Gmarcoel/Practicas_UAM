package events;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import zones.*;

public class PriceTest {

	Price p1;
	Price p2;
	StandingZone z1;
	SittingZone z2;
	
	@Before
	public void before(){
		z1 = new StandingZone("Standing 1",10);
		z2 = new SittingZone("Sitting 1",2,2);
		p1 = new Price(z1);
		p2 = new Price(z2,20);
	}

	@Test
	public void testPrice() {
		assertNotNull(p1);
		assertNotNull(p2);
		assertEquals(z1,p1.getZone());
		assertEquals(z2,p2.getZone());
		assertEquals(0,p1.getPrice(),0.5);
		assertEquals(20,p2.getPrice(),0.5);
	}

	@Test
	public void testSetPrice() {
		assertEquals(0,p1.getPrice(),0.5);
		assertEquals(20,p2.getPrice(),0.5);
		p1.setPrice(10);
		p2.setPrice(30);
		assertNotEquals(0,p1.getPrice(),0.5);
		assertEquals(10,p1.getPrice(),0.5);
		assertNotEquals(20,p2.getPrice(),0.5);
		assertEquals(30,p2.getPrice(),0.5);
	}

}
