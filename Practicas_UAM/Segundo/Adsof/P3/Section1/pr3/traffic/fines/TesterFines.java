package pr3.traffic.fines;

import pr3.traffic.drivers.*;
import pr3.traffic.vehicles.*;
import java.util.*;

public class TesterFines {
	public static void main(String[] args) {

		
		Person ann = new Person("Ann Smithing", 30);		 		// Ann 			
		Person anthony = new Person("Anthony Johnson", 27);
		Person pepe = new Person("Pepe Lagartija", 87);
		Company fdinc = new Company("Fast Delivery Inc", ann);	// Ann es responsible for FDINC
		
		anthony.setLicense(new License(PermitKind.A));
		pepe.setLicense(new License(PermitKind.A));

		Vehicle fleet[] = {
				new Car("Fiat 500x", 2019, "1245 HYN", true, ann), 	// Ann's car, who drives it		
				new Truck("IvecoDaily", 2010, "5643 KOI", 2, fdinc), // FDINC's car
				new Motorcycle("Harley Davidson", 2003, "0987 ETG", false, anthony),
				new Motorcycle("Vespa Vespino", 1954, "0345 VES", false, pepe)}; // Pepe's car but he doesn't have a license
				



				System.out.println("-------------");
				System.out.println(fleet[0]);
				System.out.println("-------------");
				System.out.println(fleet[1]);
				System.out.println("-------------");
				System.out.println(fleet[2]);
				System.out.println("-------------");
				System.out.println(fleet[3]);
				System.out.println("-------------");
				FineProcessor pm = new FineProcessor(Arrays.asList(fleet));
				pm.process(FineReader.read("./txt/fines_radar1.txt"));
	}
}
