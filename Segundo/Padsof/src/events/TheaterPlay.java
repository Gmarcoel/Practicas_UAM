package events;

import javax.persistence.*;

/**
 * This is a class that allow us to create a theater play event
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class TheaterPlay extends Event {
	private String actors;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param title       string with the title of the event
	 * @param author      String with the author of the event
	 * @param director    string that contains the director of the event
	 * @param description string with a short description of the event
	 * @param actors      string with the actors of the event
	 */
	public TheaterPlay(String title, String author, String director, String description, String actors) {
		super(title, author, director, description);
		if (title.isBlank() || author.isBlank() || director.isBlank() || description.isBlank() || actors.isBlank()) {
			System.out.println("Error:invalid string");
			return;
		}
		this.actors = actors;
	}

	/**
	 * Method to get the actors of the play
	 * 
	 * @return an string with the actors
	 */
	public String getActors() {
		return this.actors;
	}

	/**
	 * Method to set the actors of the play
	 * 
	 * @param actors to be established
	 */
	public void setActors(String actors) {
		if (actors.isBlank()) {
			System.out.println("Error:invalid string");
			return;
		}
		this.actors = actors;
	}
}