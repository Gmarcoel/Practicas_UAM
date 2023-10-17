package events;

import javax.persistence.*;

import java.io.*;
import java.time.*;
import zones.*;

/**
 * This is a class that allow us to create an annual pass
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class AnnualPass extends Pass {

	/**
	 * The start date of the annual pass
	 */
	private LocalDate startDate; 
	/**
	 * End date of the annual pass
	 */
	private LocalDate endDate;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param price of the annual pass
	 * @param zone  of the corresponding pass
	 */
	public AnnualPass(double price, Zone zone) {
		super(zone);
		if (zone == null) {
			System.out.println("Error:invalid zone");
			return;
		}
		if (price < 0) {
			System.out.println("Error:invalid price");
			return;
		}
		super.setPrice(price);
		this.startDate = LocalDate.now();
		this.endDate = LocalDate.now().plusYears(1);
	}

	/**
	 * Method that checks is an annual pass is still vigent
	 * 
	 * @return boolean if the annual pass is valid
	 */
	public boolean checkIfValidAnnualPass() {
		if (LocalDate.now().isBefore(this.endDate)) {
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Method to get the name of the annual pass
	 * 
	 * @return an string with the name
	 */
	@Override
	public String getName() {
		return "AnnualPass " + this.getStartDate().getYear() + "-" + this.getEndDate().getYear();
	}

	/**
	 * Method to get the starting date of the pass
	 * 
	 * @return localdate with the starting date
	 */
	public LocalDate getStartDate() {
		return this.startDate;
	}
	

	/**
	 * Method to get the ending date of the pass
	 * 
	 * @return localdate with the ending date
	 */
	public LocalDate getEndDate() {
		return this.endDate;
	}


	/**
	 * Method to get a copy of the actual pass
	 * 
	 * @return the copy of this pass
	 */
	@Override
	public Pass copyPass(){
		AnnualPass copyAP = new AnnualPass(this.getPrice(), this.getZone());
		return copyAP;
	}
}
