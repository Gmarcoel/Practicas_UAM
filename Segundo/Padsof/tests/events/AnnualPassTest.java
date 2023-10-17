package events;

import static org.junit.Assert.*;

import java.time.LocalDate;

import zones.*;
import org.junit.Test;
import org.junit.Before;

public class AnnualPassTest {

	AnnualPass ap1;
	StandingZone sz1;
	LocalDate d1;
	LocalDate d2;
	LocalDate d3;

	@Before
	public void before() {
		sz1 = new StandingZone("Standing 1", 20);
		ap1 = new AnnualPass(350, sz1);
	}

	@Test
	public void testAnnualPass() {
		assertEquals(sz1, ap1.getZone());
		assertEquals(350, ap1.getPrice(), 2);
		assertEquals(LocalDate.now().getYear(), ap1.getStartDate().getYear());
		assertEquals(LocalDate.now().getMonthValue(), ap1.getStartDate().getMonthValue());
		assertEquals(LocalDate.now().getDayOfMonth(), ap1.getStartDate().getDayOfMonth());
		assertEquals(LocalDate.now().plusYears(1).getYear(), ap1.getEndDate().getYear());
		assertEquals(LocalDate.now().getMonthValue(), ap1.getEndDate().getMonthValue());
		assertEquals(LocalDate.now().getDayOfMonth(), ap1.getEndDate().getDayOfMonth());
		assertEquals(ap1.getStartDate(), LocalDate.now());
		assertEquals(ap1.getEndDate(), LocalDate.now().plusYears(1));
	}

	@Test
	public void testGetName() {
		assertEquals(LocalDate.now().getYear(), ap1.getStartDate().getYear());
		assertEquals(LocalDate.now().getYear() + 1, ap1.getEndDate().getYear());
		assertEquals("AnnualPass " + LocalDate.now().getYear() + "-" + LocalDate.now().plusYears(1).getYear(),
				ap1.getName());
	}

	@Test
	public void testCheckIfValidAnnualPass() {
		assertTrue(ap1.checkIfValidAnnualPass());
	}

}
