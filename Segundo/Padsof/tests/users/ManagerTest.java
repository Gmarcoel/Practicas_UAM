package users;

import static org.junit.Assert.*;

import org.junit.Test;

public class ManagerTest {

	Manager m;

	@Test
	public final void testManager() {
		m=new Manager();
		assertTrue(m.checkCredentials("admin", "admin"));
	}

}
