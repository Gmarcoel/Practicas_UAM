package zones;

/**
 * This is a class that allow us to create a standing zone
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class StandingZone extends Zone {
	private int nMaxPeople;
	private int nPeople;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param name string with the name of the zone
	 * @param nMax int with the maximum number of people allowed in the zone
	 */
	public StandingZone(String name, int nMax) {
		super(name);
		if (name.isBlank()) {
			System.out.println("Error: Empty name \n");
			return;
		}
		if (nMax < 0) {
			System.out.println("Error: Negative number \n");
			return;
		}
		this.nMaxPeople = nMax;
		this.nPeople = 0;
	}

	/**
	 * Method to get the attendees of the standing zone
	 * 
	 * @return int with the number of attendees
	 */
	@Override
	public int getAttendees() {
		return nPeople;
	}

	/**
	 * Method to get the maximum number of people of the standing zone
	 * 
	 * @return int with the maximum number of attendees
	 */
	public int getNMaxPeople() {
		return this.nMaxPeople;
	}

	/**
	 * Method to get the number of people in a zone
	 * 
	 * @return int with the number of people
	 */
	public int getNPeople() {
		return this.nPeople;
	}

	/**
	 * Method to set the maximum number of people in the standing zone
	 * 
	 * @param n number to establish the new maximum people
	 */
	public void setNMaxPeople(int n) {
		if (n < 0) {
			System.out.println("Error: Negative number \n");
			return;
		}
		this.nMaxPeople = n;
	}

	/**
	 * Method to get the number of possible people in the standing zone
	 * 
	 * @return int with the number of possible people
	 */
    @Override
	public int getNPosPeople() {
		return ((int) ((double) this.nMaxPeople *this.occupancy / 100));
	}

	/**
	 * Method to set the number of people in the standing zone
	 * 
	 * @param n number to be established
	 */
	public void setNPeople(int n) {
		if (n < 0) {
			System.out.println("Error: Empty name \n");
			return;
		} else if (this.nMaxPeople < n) {
			System.out.println("too many people");
			return;
		} else {
			this.nPeople = n;
		}
	}

	/**
	 * Method that checks if the zone is full or not
	 * 
	 * @return boolean if it is fully occuopied
	 */
	public boolean isOccupied() {
		if (this.getNPosPeople() - this.nPeople > 0) {
			return false;
		}
		return true;
	}

	/**
	 * Method reduces the number of people by one on that zone
	 * 
	 * @param n with the new num of people
	 */
	public void reduceNPeople(int n) {
		if (n < 0) {
			System.out.println("Error: Negative number \n");
			return;
		} else if (this.getNPosPeople() < n) {
			System.out.println("Error: Number is too large \n");
			return;
		}
		this.setNPeople(this.getNPeople() - n);
	}

	/**
	 * Method that occupy a single space in the zone
	 */
	public void occupy() {
		if (this.isOccupied()) {
			System.out.println("The zone is already full");
			return;
		} else {
			this.nPeople++;
		}
	}

	/**
	 * Method that frees a single space in the zone
	 */
	public void free() {
		if (this.getAttendees() == 0) {
			System.out.println("The zone is already empty");
			return;
		} else {
			this.nPeople--;
		}
	}

	/**
	 * Method that clonates the standing zone
	 *
	 * @return zone cloned
	 */
	@Override
	public Zone cloneZone() {
		return new StandingZone(this.getName(), this.nMaxPeople);
	}
}
