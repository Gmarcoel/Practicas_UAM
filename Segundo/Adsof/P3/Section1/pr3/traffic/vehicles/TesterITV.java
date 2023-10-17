package pr3.traffic.vehicles;

import pr3.traffic.fines.*;
import pr3.traffic.drivers.*;
import java.util.*;

public class TesterITV {
    public static void main(String[] args) {
		Person ann = new Person("Ann Smith", 30);		 		// Ann 			
		Person anthony = new Person("Anthony Johnson", 27);
    Person pepe = new Person("Pepe Lagartija",87);
		Company fdinc = new Company("Fast Delivery Inc", pepe);	// Pepe is responsible for FDINC
		
		ann.setLicense(new License(PermitKind.B, PermitKind.C1));
		anthony.setLicense(new License(PermitKind.A));
    pepe.setLicense(new License(PermitKind.C1));
		
		Vehicle fleet[] = { 
				new Car("Fiat 500x", 2019, "1245 HYN", true, ann), 	// Ann's car, who drives it		
				new Truck("IvecoDaily", 2010, "5643 KOI", 2, fdinc), // FDINC's car
				new Motorcycle("Harley Davidson", 2003, "0987 ETG", false, anthony)};

        Garage places[] = { // garages to do the ITV
            new Garage("West Coast Customs", "Los Santos 3", "San Andreas"),
            new Garage("Talleres Manolo", "Calle de la Concepción, 4", "Albacete"),
            new Garage("Huelva tunin", "plaza de Huelva", "Huelva")};

		ITV itvs[] = {  // ITVs of the different vehicles
            new ITV(2019,02,20, places[0],"Everything ok"),
            new ITV(2016,05,16, places[0],"Everything was wrong change your car"),
            new ITV(2014,05,14, places[0],"Problems on left suspension"),
            new ITV(2020,02,20, places[1],"Oil consuption"),
            new ITV(2004,02,20, places[2],"Check wheels")};
            

        fleet[0].addITV(itvs[0]);
        fleet[1].addITV(itvs[1]);
        fleet[1].addITV(itvs[2]);
        fleet[2].addITV(itvs[3]);

        System.out.println("===============\nVehicles that passed itv at West Coast Customs: \n" + places[0].showVehicles()); //This should show the first and second vehicles (ann's and fdnic's)

		FineProcessor pm = new FineProcessor(Arrays.asList(fleet));
		pm.process(FineReader.read("txt/fines_radar1.txt"));
	}
    
}
