// add imports and package
public class TesterLicense {
	private void testYoungerThan18CannotHavePermitA() {
		Person ann = new Person("Ann Smith", 17);
		License c = new License(PermitKind.A);
		System.out.println("Test: YoungerThan18CannotHavePermitA");
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
	
	public static void main(String[] args) {
		TesterLicense tap3 = new TesterLicense();
		tap3.testYoungerThan18CannotHavePermitA();
		tap3.testYoungerThan23CannotHavePermitC1();
		tap3.testLicenseForVehicleKind();
	}	
}
