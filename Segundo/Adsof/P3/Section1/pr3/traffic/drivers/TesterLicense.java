package pr3.traffic.drivers;

import pr3.traffic.vehicles.*;

public class TesterLicense {
	private void testYoungerThan18CannotHavePermitA() {
		Person ann = new Person("Ann Smith", 17);
		License c = new License(PermitKind.A);
		System.out.println("=================\nTest: YoungerThan18CannotHavePermitA");
		System.out.println(c);
		System.out.println(ann.setLicense(c));		// should return false, since Ann is not 18 years old		
	}
	
	private void testYoungerThan23CannotHavePermitC1() {
		Person ann = new Person("Ann Smith", 19);
		License c = new License(PermitKind.A, PermitKind.C1);
		System.out.println("=================\nTest: YoungerThan23CannotHavePermitC1");
		System.out.println(c);			
		System.out.println(ann.setLicense(c));		// should return false, since Ann is not 23 years old
	}
	
	private void testLicenseForVehicleKind() {
		Person ann = new Person("Ann Smith", 24);
		ann.setLicense(new License(PermitKind.A, PermitKind.C1));
		Car c = new Car("Fiat 500x", 2019, "1245 HYN", true, ann);
		System.out.println("=================\nTest: LicenseForVehicleKind");
		System.out.println(c);		// Ann is not the driver, since it has motorbyke and truck permits
		ann.getLicense().addPermit(PermitKind.B);
		c.setDriver(ann);
		System.out.println(c);		// Now she is
		System.out.println(ann.getLicense());		// license
	}

	private void testInitialPoints() {
		Person ann = new Person("Ann Smith", 24);
		ann.setLicense(new License(PermitKind.A, PermitKind.C1));
		System.out.println("=================\nTest: InitialPoints");
		System.out.println("Points: " + ann.getLicense().getPoints()); //Expect 12 points from a new license
	}

	private void testThreeLicenses() {
		Person paco = new Person("Paco Pérez", 56);
		paco.setLicense(new License(PermitKind.B,PermitKind.A, PermitKind.C1));
		System.out.println("=================\nTest: ThreeLicenses");
		System.out.println(paco.getLicense()); //Expects a license with tree permits
	}
	private void testTwoLicenses() {
		Person paco = new Person("Paco Pérez", 56);
		paco.setLicense(new License(PermitKind.B,PermitKind.A));
		System.out.println("=================\nTest: TwoLicenses");
		System.out.println(paco.getLicense()); // Expects a licence with two permits
	}
	private void testOneLicense() {
		Person paco = new Person("Paco Pérez", 56);
		paco.setLicense(new License(PermitKind.C1));
		System.out.println("=================\nTest: Onelicense");
		System.out.println(paco.getLicense());  // Expects a licence with  licence one permits
	}
	private void testNoLicencesAddOne() {
		Person paco = new Person("Paco Pérez", 56);
		System.out.println("=================\nTest: NoLicensesAddOne");
		System.out.println(paco.getLicense()); // Expects null because there is no license
		paco.setLicense(new License(PermitKind.A));
		System.out.println(paco.getLicense()); // Expects a permit to be added to a new license
	}

	private void removePoints() {
		Person pepe = new Person("Pepe Lagartija", 87);
		pepe.setLicense(new License(PermitKind.B, PermitKind.C1));
		System.out.println("=================\nTest: RemovePoints");
		pepe.getLicense().removePoints(8);
		System.out.println(pepe.getLicense()); 
	}

	public static void main(String[] args) {
		TesterLicense tap3 = new TesterLicense();
		tap3.testYoungerThan18CannotHavePermitA();
		tap3.testYoungerThan23CannotHavePermitC1();
		tap3.testLicenseForVehicleKind();
		tap3.testInitialPoints();
		tap3.testThreeLicenses();
		tap3.testTwoLicenses();
		tap3.testOneLicense();
		tap3.testNoLicencesAddOne();
		tap3.removePoints();


	}	

}
