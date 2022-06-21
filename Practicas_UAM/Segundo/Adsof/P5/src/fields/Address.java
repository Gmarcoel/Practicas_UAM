package fields;


/**
* Class that stores the data of the type address
*
* @author ADSOF teachers
*/
public class Address implements Comparable<Address>{
	private String address;
	private int postalCode;

	/**
	* constructor for the class address
	* 
	* @param adr	 String with the address
	* @param pc 	 integer with the postal code
	*/
	public Address(String adr, int pc) {
		this.address = adr;
		this.postalCode = pc;
	}

	
	/**
	* getter for the postal code of the address
	*
	* @return integer with the postal code
	*/
	public int postalCode() {
		return this.postalCode;
	}

	
	/**
	* function to print the address
	*
	* @return a string with the resulting output
	*/
	public String toString() {
		return this.address + " at PC(" + this.postalCode + ")";
	}

	@Override
    public int compareTo(Address address){
        int n;
        n = this.postalCode - address.postalCode;

        if (n==0){
            n = this.address.compareTo(address.address);
        }

        return n;
    }
    
}
