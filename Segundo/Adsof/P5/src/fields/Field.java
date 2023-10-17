package fields;
import java.util.function.Predicate;
import java.util.function.Function;
import java.util.*;
/**
* Class that stores the fields
*
* @author Daniel Varela and Guillermo Martín-Coello
*/
public class Field<E extends Comparable<E>> implements Comparable<Field<E>>{
	private E value;
	private Function<String, E> f;
	private HashMap<Predicate<E> , String> validation = new HashMap<>();
	
	/**
	 * Constructor of Field class
	 * @param f function to get the field type
	 */
	public Field(Function<String, E> f) {
		this.f = f;
		
	}
	/**
	 * returns a copy of the class
	 * @return copy of field
	 */
	public Field<E> duplicateField() {
		Field<E> newField = new Field<E>(this.f);
		newField.value = this.value;
		newField.validation = new HashMap<Predicate<E>, String>(this.validation);
		return newField;
	}
	
	/**
	 * to string method
	 * @return string of the class
	 */
	@Override 
	public String toString() {
		return this.value.toString();
	}
	


	/**
	 * adds a new validation to the field
	 * @param f function of the field type
	 * @param s validation
	 * @return this field
	 */
	public Field<E> addValidation(Predicate<E> f, String s) {
		this.validation.put(f,s);
		return this;
	}
	/**
	 * Checks if answer is valid
	 * @param s given answer
	 * @return true if valid
	 */
	public boolean answer(String s){
    	for (Map.Entry<Predicate<E> , String> item  : validation.entrySet())	
    	{
    		if(!(item.getKey().test(this.f.apply(s))))	{
    			System.out.println("Invalid value: " + s);
    			System.out.println("	" + item.getValue());
    			return false;
    		}	
    	}
		this.value = this.f.apply(s);
		return true;
	}
	/**
	 * method of comparing
	 * @param f field to compare to
	 * @return 0 if equal
	 */
	@Override
	public int compareTo(Field<E> f) {
		int n;
		n = this.value.compareTo(f.value);
		return n;
	}



}