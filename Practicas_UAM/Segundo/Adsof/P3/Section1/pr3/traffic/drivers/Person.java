package pr3.traffic.drivers;

/**
 * This is a class for the Person attributes
 * 
 * @author Guillermo Martin-Coello and Daniel Varela
 */
public class Person extends User {
	private int age;
	private License license;

	/**
	 * This function serves as a constructor of the class Person
	 * 
	 * @param name the name of the Person object
	 * @param age  the age of the person
	 */
	public Person(String name, int age) {
		super(name);
		this.age = age;
	}




	/**
 	* Function that sets license for driver
 	* @param license
	*/
	public boolean setLicense(License license){
		if(license.checkLegalAge(this.age)==true){
			license.addOwner(this);
			this.license = license;
			return true;
		}
		return false;
	}
	
	/**
	 * Function that returns the license of a person
	 * 
	 * @return the license of the person
	 */
	public License getLicense(){
		return this.license;
	}

	/**
	 * Function that returns the age of a person
	 * 
	 * @return the age of the person
	 */
	public int getAge(){
		return this.age;
	}

	/**
	 * Function to print Person information
	 * 
	 * @return It returns the information you need to print when the User is of type
	 *         Person
	 */
	@Override
	public String toString() {
		return getName() + super.toString();
	}


}
