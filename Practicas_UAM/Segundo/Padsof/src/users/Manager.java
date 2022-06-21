package users;

/**
 * This is a class that allow us to create a manager
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class Manager extends RegisteredUser {

	/**
	 * Constructor with predefined parameters to create a manager
	 */
	public Manager() {
		super("admin", "admin");
	}

}
