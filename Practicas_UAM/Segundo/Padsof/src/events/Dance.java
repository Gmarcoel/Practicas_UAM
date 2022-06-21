package events;

import javax.persistence.*;

/**
 * This is a class that allow us to create a dance event
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */

public class Dance extends Event {
	private String conductor;
	private String dancer;
	private String orchestra;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param title       string with the title of the event
	 * @param author      String with the author of the event
	 * @param director    string that contains the director of the event
	 * @param description string with a short description of the event
	 * @param conductor   string with the conductor of the event
	 * @param dancer      string with the dancers of the event
	 * @param orchestra   string with the orchestra of the event
	 */
	public Dance(String title, String author, String director, String description, String conductor, String dancer,
			String orchestra) {

		super(title, author, director, description);

		if (title.isBlank() || author.isBlank() || director.isBlank() || description.isBlank() || conductor.isBlank()
				|| dancer.isBlank()) {
			System.out.println("Error:invalid string");
			return;
		}

		this.conductor = conductor;
		this.dancer = dancer;
		this.orchestra = orchestra;
	}

	/**
	 * Method to get the conductor of the dance event
	 * 
	 * @return an string with the conductor
	 */
	public String getConductor() {
		return this.conductor;
	}

	/**
	 * Method to get the dancer of the dance event
	 * 
	 * @return an string with the dancer
	 */
	public String getDancer() {
		return this.dancer;
	}

	/**
	 * Method to get the orchestra of the dance event
	 * 
	 * @return an string with the orchestra
	 */
	public String getOrchestra() {
		return this.orchestra;
	}

	/**
	 * Method to set the conductor of an event
	 * 
	 * @param conductor to be established
	 */
	public void setConductor(String conductor) {
		if (conductor.isBlank()) {
			System.out.println("Error:invalid string");
		}
		this.conductor = conductor;
	}

	/**
	 * Method to set the dancers of an event
	 * 
	 * @param dancer to be established
	 */
	public void setDancer(String dancer) {
		if (dancer.isBlank()) {
			System.out.println("Error:invalid string");
		}
		this.dancer = dancer;
	}

	/**
	 * Method to set the orchestra of an event
	 * 
	 * @param orchestra to be established
	 */
	public void setOrchestra(String orchestra) {
		if (orchestra.isBlank()) {
			System.out.println("Error:invalid string");
		}
		this.orchestra = orchestra;
	}
}