package forms;

import java.io.IOException;
import java.util.LinkedHashMap;

import fields.Field;

import java.io.BufferedReader;
import java.io.InputStreamReader;


/**
* Class that stores a protected form
*
* @author Daniel Varela and Guillermo Martín-Coello
*/
public class ProtectedForm implements AbstractForm{
    private boolean protect = false;
    private String password;
    private Form form;

    /**
    * constructor for the class ProtectedForm
    *
    * @param p      wether the form is protected or  not
    * @param f      the original form
    * @param pass   the string with the password
    */
    public ProtectedForm(boolean p, Form f, String pass ){
        this.protect=p;
        this.form=f;
        this.password=pass;
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
	public Form add(String question, Field<?> f) {
		this.form.add(question, f);
		return null;
	}

	
	/**
    * Sets the form as protected 
    * 
    * @param f      the form that you want to protect
    * @param p      the password for the form
    * @return a protected Abstract Form with te password of the class
    */
    public static AbstractForm protect(Form f, String p){
    	return new ProtectedForm(true, f, p); 
    }
    
    

	/**
	* allows the user to answer the form 
	*
    * @throws IOException   exception for when reading input fails
	* @return the resulting hash map with all the questions and answers
	*/
	@Override
	public LinkedHashMap<String, Field<? extends Comparable<?>>> exec() throws IOException {
        int i=1;
        String input;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        if(this.protect==true){
            
        while (i<=3){
            System.out.println("Enter password: ");
            input = br.readLine();
            if(this.password.equals(input)){
                this.protect=false;
                return this.form.exec();
            }
            System.out.println("Invalid password ("+(3-i)+" remaining attempts)");
            i++;
        }
        System.out.println("You failed the password 3 times, form not available");
        return null;
        }
        
        return this.form.exec();
    }
    
    


}