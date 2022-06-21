package zones;

import static org.junit.Assert.*;
import java.time.*;

import org.junit.Test;
import org.junit.Before;

public class MaintenanceSeatTest {
	MaintenanceSeat ms1;
	MaintenanceSeat ms2;
	MaintenanceSeat ms3;
	MaintenanceSeat ms4;
	MaintenanceSeat ms5;
	LocalDate ld1;
	LocalDate ld2;
	LocalDate ld3;
	LocalDate ld4;
	
	@Before
	public void before() {
		ld1 = LocalDate.of(2022,01,01);
		ld2 = LocalDate.of(2024,03,19);
		ld3 = LocalDate.of(2032,02,22);
		ld4 = LocalDate.of(2001,03,04);
		ms1 = new MaintenanceSeat(ld1,"Mantenimiento 1");
		ms2 = new MaintenanceSeat(ld2,"Mantenimiento 2");
		ms3 = new MaintenanceSeat(ld3,"Mantenimiento 3");
		ms4 = new MaintenanceSeat(ld4,"Mantenimiento 4");
		ms5 = new MaintenanceSeat(ld4,"Mantenimiento 4");		
	}

	@Test
	public void testMaintenanceSeat() {
		assertNotEquals(ms1,ms2);
		assertNotEquals(ms4,ms5);
		assertEquals(ms4.getEndDate(),ms5.getEndDate());
	}


	@Test
	public void testSetDate() {
		assertEquals(ms1.getEndDate(),ld1);
		ms1.setDate(ld2);
		assertEquals(ms1.getEndDate(),ld2);
		ms1.setDate(ld1);
		assertNotEquals(ms1.getEndDate(),ld2);
	}

	@Test
	public void testSetNotes() {
		assertEquals(ms3.getNotes(),"Mantenimiento 3");
		ms3.setNotes("Cambio de notas");
		assertEquals(ms3.getNotes(),"Cambio de notas");
		ms3.setNotes("Mantenimiento 3");
		assertNotEquals(ms3.getNotes(),"Cambio de notas");
	}

	@Test
	public void testMaintainedSeatVigent() {
		assertTrue(ms2.maintainedSeatVigent());
		//assertFalse(ms4.maintainedSeatVigent());
	}

}
