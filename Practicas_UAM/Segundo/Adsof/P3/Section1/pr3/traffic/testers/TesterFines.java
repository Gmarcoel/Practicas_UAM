// add imports and package
public class TesterFines {
	public static void main(String[] args) {
		Person ann = new Person("Ann Smith", 30);		 		// Ann 			
		Person anthony = new Person("Anthony Johnson", 27);
		Company fdinc = new Company("Fast Delivery Inc", ann);	// Ann es responsible for FDINC
		
		ann.setLicense(new License(PermitKind.B, PermitKind.C1));
		anthony.setLicense(new License(PermitKind.A));
		
		Vehicle fleet[] = { 
				new Car("Fiat 500x", 2019, "1245 HYN", true, ann), 	// Ann's car, who drives it		
				new Truck("IvecoDaily", 2010, "5643 KOI", 2, fdinc), // FDINC's car
				new Motorcycle("Harley Davidson", 2003, "0987 ETG", false, anthony)};
		
		FineProcessor pm = new FineProcessor(Arrays.asList(fleet));
		pm.process(FineReader.read("fines_radar1.txt"));
	}
}
