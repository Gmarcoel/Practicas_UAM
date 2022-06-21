package pr3.traffic.drivers;

/**
 * This is a class for the vehicles common attributes
 * 
 * @author Guillermo Martin-Coello and Daniel Varela
 */
public class Company extends User {
	private Person responsible;

	/**
	 * This function serves as a constructor of the class Company
	 * 
	 * @param name        the name of the company object
	 * @param responsible the responsible person of the company
	 */
	public Company(String name, Person responsible) {
		super(name);
		this.responsible = responsible;
	}

	/**
	 * Function that returns the responsible of the company
	 * 
	 * @return the person responsible
	 */
	public Person getResponsible() {
		return this.responsible;
	}

	/**
	 * Function to print Company information
	 * 
	 * @return It returns the information you need to print when the User is of type
	 *         Companty
	 */
	@Override
	public String toString() {
		return getName() + " (responsible: " + this.responsible.getName() + ") " + super.toString();
	}
}
