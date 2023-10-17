package statistics;

import static org.junit.Assert.*;



import org.junit.Before;

import zones.*;

import org.junit.Test;

import events.*;
import performances.*;

import java.time.LocalDateTime;
import java.util.*;
public class EventStatisticTest {

	StandingZone stz1;
	StandingZone stz2;
	StandingZone stz3;
	SittingZone sz1;
	SittingZone sz2;
	SittingZone sz3;
	Seat seat1;
	Seat seat2;
	Seat seat3;
	FragmentedZone fz1;
	FragmentedZone fz2;
	EventStatistic stats1;
	Dance e1;
	Concert e2;
	TheaterPlay e3;
	Performance p1;
	Performance p2;
	Performance p3;
	ArrayList<Zone> zones;
	ArrayList<Event> events;
	
	@Before
	public void before() {
		stz1 = new StandingZone("Standing 1", 10);
		stz2 = new StandingZone("Standing 2", 15);
		stz3 = new StandingZone("Standing 3", 20);
		sz1 = new SittingZone("Sitting 1", 2,2);
		sz2 = new SittingZone("Sitting 2", 3,2);
		sz3 = new SittingZone("Sitting 3", 2,4);
		fz1 = new FragmentedZone("Fragmented 1");
		fz2 = new FragmentedZone("Fragmented 2");
		
		seat1 = new Seat(0,1);
		seat2 = new Seat(1,1);
		seat3 = new Seat(2,0);
		
		fz1.addSubzone(stz1);
		fz1.addSubzone(sz1);
		
		fz2.addSubzone(stz2);
		fz2.addSubzone(sz2);
		fz1.addSubzone(fz2);

		
		zones = new ArrayList<>();
		zones.add(fz1);
		zones.add(stz3);
		zones.add(sz3);
		
		stats1 = new EventStatistic("Stats 1",e1);

		
		e1 = new Dance("Swan lake", "Dostoievski", "Pepe Lagartija", "Beautiful movements", "Messi", "Richard Widmark",
				"National Band");
		e2 = new Concert("RDR2 Soundtrack", "D'Angelo", "Pepe Lagartija", "Musical masterpiece", "Unshaken, Cruel World, Moonlight",
				"National Band");
		e3 = new TheaterPlay("Romeo & Juliet", "Shakespeare", "Pepe Lagartija", "Two lovers, one destiny",
				"Danielo, Guillerma");
		
		events = new ArrayList<>();
		events.add(e1);
		events.add(e2);
		
		
		e1.createPerformance(LocalDateTime.of(2021, 7, 27, 7, 00), zones);
		e1.createPerformance(LocalDateTime.of(2021, 11, 12, 10, 30), zones);
		e2.createPerformance(LocalDateTime.of(2021, 11, 15, 11, 15), zones);
		p1 = e1.getPerformance(LocalDateTime.of(2021, 7, 27, 7, 00));
		p2 = e1.getPerformance(LocalDateTime.of(2021, 11, 12, 10, 30));
		p3 = e2.getPerformance(LocalDateTime.of(2021, 11, 15, 11, 15));
		/**/
		e1.setPrice(sz1, 4); //4
		e1.setPrice(sz2, 11); //6
		e1.setPrice(sz3, 41); //8
		e1.setPrice(stz1, 5); //10
		e1.setPrice(stz2, 5); //15
		e1.setPrice(stz3,7); //20
		e2.setPrice(sz1, 7); //4
		e2.setPrice(sz2, 8); //6
		e2.setPrice(sz3, 9); //8
		e2.setPrice(stz1, 10); //10
		e2.setPrice(stz2, 11); //15
		e2.setPrice(stz3,12); //20
		p1.getZone(fz1).setOccupancy(50); // 35/2 = 17'5
	}
	@Test
	public final void testEventStatistic() {
		((SittingZone)p1.getZone(sz1)).occupy(seat1); // 4
		p1.getZone(stz1).occupy(); //15
		p1.getZone(stz1).occupy();
		p1.getZone(stz1).occupy();
		((SittingZone)p2.getZone(sz2)).occupy(seat1); // 22
		((SittingZone)p2.getZone(sz2)).occupy(seat2);
		p2.getZone(stz1).occupy();  // 5
		p2.getZone(stz2).occupy();	// 10
		p2.getZone(stz2).occupy();
		((SittingZone)p3.getZone(sz2)).occupy(seat1);
		((SittingZone)p3.getZone(sz2)).occupy(seat2);
		p3.getZone(stz1).occupy(); 
		p3.getZone(stz2).occupy();	
		p3.getZone(stz2).occupy();	
		stats1.updateStatistics(e1);
		assertEquals(8,stats1.getOccupancy(),.5); 
		assertEquals(56,stats1.getProfits(),.5);
	}
}