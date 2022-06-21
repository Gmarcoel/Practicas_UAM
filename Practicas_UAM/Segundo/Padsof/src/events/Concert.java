package events;
import java.io.*;
import javax.persistence.*;

/**
 * This is a class that allow us to create a concert event
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class Concert extends Event {
	private String musicPieces;
	private String orchestra;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param title       string with the title of the event
	 * @param author      String with the author of the event
	 * @param director    string that contains the director of the event
	 * @param description string with a short description of the event
	 * @param musicPieces string with the music pieces of the event
	 * @param orchestra   string with the orchestra of the event
	 */
	public Concert(String title, String author, String director, String description, String musicPieces,
			String orchestra) {

		super(title, author, director, description);

		if (title.isBlank() || author.isBlank() || director.isBlank() || description.isBlank() || musicPieces.isBlank()
				|| orchestra.isBlank()) {
			System.out.println("Error:invalid string");
			return;

		}
		this.musicPieces = musicPieces;
		this.orchestra = orchestra;
	}

	/**
	 * Method to get the music pieces of the concert
	 * 
	 * @return an string with the music pieces
	 */
	public String getMusicPieces() {
		return this.musicPieces;
	}

	/**
	 * Method to get the orchestra of the concert
	 * 
	 * @return an string with the orchestra
	 */
	public String getOrchestra() {
		return this.orchestra;
	}

	/**
	 * Method to set the music pieces of the concert
	 * 
	 * @param mp to be established
	 */
	public void setMusicPieces(String mp) {
		if (mp.isBlank()) {
			System.out.println("Error:invalid string");
			return;
		}
		this.musicPieces = mp;
	}

	/**
	 * Method to set the orchestra of the concert
	 * 
	 * @param o to be established
	 */
	public void setOrchestra(String o) {
		this.orchestra = o;
	}

}