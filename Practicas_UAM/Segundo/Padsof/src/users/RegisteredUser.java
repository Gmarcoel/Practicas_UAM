package users;

import java.io.*;
import java.security.MessageDigest;
import java.util.Base64;
import java.util.Base64.*;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;
import javax.persistence.*;

/**
 * This is an abstract class that allow us to define a registered user
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public abstract class RegisteredUser implements Serializable {

	private String username;
	private String password;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param username string with the username of the user
	 * @param password String with the password of the user
	 */
	public RegisteredUser(String username, String password) {
		if (username == null || password == null) {
			System.out.println("Error: RegisteredUser constructor recieves a null argument\n");
			return;
		}
		this.username = username;
		this.password = cypher(password);
	}


	/**
	 * Method to cypher the password of the user
	 * 
	 * @param password not cyphered
	 * @return string with the cifrated password
	 */
	public String cypher(String password){
		Encoder encoder = Base64.getEncoder();
		String originalinput = password;
		String encoded = encoder.encodeToString(originalinput.getBytes());
		return encoded;
	}

	/**
	 * Method to deCypher the password of the user
	 * 
	 * @param password cifrated
	 * @return string with the decifrated password
	 */
	public String deCypher(String password){
		Decoder decoder = Base64.getDecoder();
		byte[] bytes = decoder.decode(password);
		return new String(bytes);
	}

	/**
	 * Method to get the username of a user
	 * 
	 * @return string with the username
	 */
	public String getUsername() {
		return this.username;
	}

	/**
	 * Method to get the password of a user
	 * 
	 * @return string with the password
	 */
	public String getPassword() {
		return this.password;
	}

	/**
	 * Method that checks the credentials of a user given a username and a password
	 * 
	 * @param username to compare with
	 * @param pass to compare with
	 * 
	 * @return if the user is valid
	 * 
	 */
	public boolean checkCredentials(String username, String pass) {
		if (username == null || pass == null) {
			System.out.println("Error: checkCredentials method in RegisteredUser recieves a null argument\n");
			return false;
		}
		if (username.equals(this.username) && pass.equals(deCypher(this.getPassword()))) {
			return true;
		}
		return false;
	}

	
}
