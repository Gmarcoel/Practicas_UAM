package users;

import static org.junit.Assert.*;

import org.junit.Test;
import org.junit.Before;

public class RegisteredUserTest {
	
	Customer c1;
	Customer c2;
	Customer c3;
	Manager m;

	@Before
	public void before(){
		c1 = new Customer("Paco", "pacopassword");
		c2 = new Customer("Pepe", "pepemotorista");
		c3 = new Customer("Miguel", "contrasena");
		m= new Manager();
	}

	@Test
	public void testGetUsername() {
		assertEquals(c1.getUsername(), "Paco");
		assertEquals(c2.getUsername(), "Pepe");
		assertEquals(c3.getUsername(), "Miguel");
		assertEquals(m.getUsername(), "admin");
	}

	@Test
	public void testGetpassword() {
		assertEquals(c1.deCypher(c1.getPassword()), "pacopassword");
		assertEquals(c2.deCypher(c2.getPassword()), "pepemotorista");
		assertEquals(c3.deCypher(c3.getPassword()), "contrasena");
		assertEquals(m.deCypher(m.getPassword()), "admin");
	}

	@Test
	public void testChekCreadentials() {
		assertFalse(c1.checkCredentials("Juan", "admin"));
		assertFalse(c2.checkCredentials("admin", "contrasena"));
		assertFalse(c3.checkCredentials("Alfred", "admin"));
		assertTrue(m.checkCredentials("admin", "admin"));
	}

}
