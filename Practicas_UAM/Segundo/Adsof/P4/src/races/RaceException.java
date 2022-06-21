package races;
/**
 * Race exception class
 * 
 * @author Daniel Varela & Guillermo Martín-Coello
 *
 */
public class RaceException extends Exception {
	/**
	 * serial version
	 * @return serial version
	 */
	private static final long serialVersionUID = 1L;

	public RaceException() {
		super();
	}

	/**
	 * Prints class information through output
	 * @return String with the error message
	 */
	@Override
	public String toString() {
		return "Race exception error";
	}
}
