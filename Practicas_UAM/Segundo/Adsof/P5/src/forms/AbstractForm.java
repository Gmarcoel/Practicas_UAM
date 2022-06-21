package forms;

import java.io.IOException;
import java.util.LinkedHashMap;

import fields.Field;

/**
 * Abstract interface of the form
 * 
 * @author Daniel Varela and Guillermo Martín-Coello
 *
 */
public interface AbstractForm	{
	/**
	* adds a new question to the form 
	* 
	* @param question 	the string of the question 
	* @param f			the field with the type of the answer
	*
	* @return the form after adding the question
	*/
	public Form add (String question, Field<?> f);

	
	/**
	* allows the user to answer the form 
	*
    * @throws IOException   exception for when reading input fails
	* @return the resulting hash map with all the questions and answers
	*/
	public LinkedHashMap<String, Field<? extends Comparable<?>>> exec() throws IOException;
}
