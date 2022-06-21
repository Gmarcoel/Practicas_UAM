package forms;



import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.Map.Entry;
import fields.Field;

/**
* Class that stores the data of the type address
*
* @author Daniel Varela and Guillermo Martín-Coello
*/
public class DataAggregator {
	private LinkedHashMap<String, ArrayList<Field<? extends Comparable<?>>>> data = new LinkedHashMap<>();
	/**
	 * Constructor for the data aggregator class
	 */
	public DataAggregator() {
		data = new LinkedHashMap<>();
	}
	/**
	 * Method to add new fields to the data aggregator
	 * @param map map with all the questions and their respective answers
	 */
	public void add(LinkedHashMap<String, Field<? extends Comparable<?>>> map)	{
		
		for (Entry<String, Field<? extends Comparable<?>>> item  : map.entrySet())	{
			if(!(data.containsKey(item.getKey())))	{
				data.put(item.getKey(), new ArrayList<>());
			}
			data.get(item.getKey()).add((item.getValue().duplicateField()));
			Collections.sort(data.get(item.getKey()));
		}
	}
	/**
	 * to string method
	 *
	 * @return string of the class
	 */
	@Override
	public String toString()
	{
		return this.data.toString();
	}
}