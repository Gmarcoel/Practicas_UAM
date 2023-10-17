package performances;

import users.*;
import zones.*;
import events.*;
import java.time.LocalDateTime;
import java.util.*;
import org.junit.Test;
import org.junit.Before;

public class WaitListTest {

	
	Customer c1;
	Customer c2;
	Customer c3;
	Performance p;
	SittingZone sz1;
	StandingZone stz1;
	TheaterPlay e;
	WaitList wl;

	@Before
	public void before(){
		c1 = new Customer("Paco", "pacopassword");
		c2 = new Customer("Pepe Lagartija", "pepeLagartoYSUVESPINO87");
		c3 = new Customer("Miguel", "contrasena");
		sz1 = new SittingZone("Sitting 1", 4, 4);
		stz1 = new StandingZone("Standing 1", 10);
		ArrayList<Zone> zones = new ArrayList<Zone>();
		zones.add(sz1);
		zones.add(stz1);
		e = new TheaterPlay("Romeo y Julieta", "W.Shakespeare", "Paco Piedra", "Una obra sobre amor", "Actor1 Actor2 Actor3");
		p =new Performance(LocalDateTime.of(2021, 9, 9, 10, 30), zones, e);
		
	}

	@Test
	public void testWaitList() {
		
	}


}