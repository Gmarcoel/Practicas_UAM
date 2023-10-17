
package prac2.traffic;

/**
 * This is an enum class that stores the pollution index
 * @author Juan De Lara
 * 
 * {@link #A}
 * {@link #B}
 * {@link #C}
 */

public enum PollutionIndex {
	/**
	 * A pollution index
	 */
	A, 
	
	/**
	 * B pollution index
	 */
	B, 
	
	/**
	 * C pollution index
	 */
	C;
	
	private static final int DATEA = 2018;
	private static final int DATEB = 2010;
	
	/**
	 * @return If the year is after or equal to 2018 it returns an A pollutionIndex, if it's earlier than 2018 but after 2010
	 * it returns B pollutionIndex and if it's earlier than 2010 it returns C.
	 * @param year a parameter that indicates the year of purchase of the car
	 */
	public static PollutionIndex getPollutionIndex(int year) {
		if (year >= DATEA) return A;
		if (year >= DATEB) return B;
		return C;
	}
}
