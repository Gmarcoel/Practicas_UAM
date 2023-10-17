package forms;

import java.util.*;
import java.util.Map.Entry;

import fields.Field;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;


/**
* Class that stores the different fields of the form 
*
* @author Daniel Varela and Guillermo Martín-Coello
*/
public class Form implements AbstractForm {
    private LinkedHashMap<String, Field<? extends Comparable<?>>> fields = new LinkedHashMap<>();

    /**
    * constructor for the class form
    */
    public Form(){
    	
    }
    
	/**
	* adds a new question to the form 
	* 
	* @param question 	the string of the question 
	* @param f			the field with the type of the answer
	*
	* @return the form after adding the question
	*/
    @Override
    public Form add (String question, Field<?> f) {
        this.fields.put(question, f.duplicateField());
        return this;
    }
    
	/**
	* allows the user to answer the form 
	*
    * @throws IOException   exception for when reading input fails
	* @return the resulting hash map with all the questions and answers
	*/
    @Override
    public LinkedHashMap<String, Field<? extends Comparable<?>>> exec() throws IOException	{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    	for (Entry<String, Field<? extends Comparable<?>>> item  : fields.entrySet())	{
    		String question = item.getKey();
    		Field<?> answer = item.getValue();
            
                System.out.println(question+" > ");
            
                String s = br.readLine();

            while(answer.answer(s)==false){
                System.out.println(question+" > ");
            
                s = br.readLine();
            }
            
    	}
        return this.fields;
    }
}