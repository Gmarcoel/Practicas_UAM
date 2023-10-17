package components;


public class InvalidComponentException extends Exception {
	/**
	 * serial version
	 * @return serial version
	 */
	private static final long serialVersionUID = 1L;

	public InvalidComponentException() {
		super();
		
	}

	/**
	* Prints the invalid component error 
	* @return String with the error message
	*/
    @Override 
    public String toString(){
        return "InvalidComponentException error";
    }
}
