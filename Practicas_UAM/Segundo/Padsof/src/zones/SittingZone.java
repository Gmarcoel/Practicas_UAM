package zones;

/**
 * This is a class that allow us to create a sitting zone
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class SittingZone extends Zone {
 
    private int nRows;
    private int nColumns;
    private Seat[][] matrix;
    private double occupiedSeats;
	
	/**
	 * Constructor, with the attributes
	 * 
	 * @param name string with the name of the zone
	 * @param nRows int with the number of rows in the sitting zone
	 * @param nColumns int with the number of columns in the sitting zone
	 */
    public SittingZone(String name, int nRows, int nColumns) {
        super(name);
    	if(name.isBlank()) {
    		System.out.println("Error: Empty name \n");
    		return;
    	}
    	if(nRows <0) {
    		System.out.println("Error: Negative number of rows\n");
    		return;
    	}
    	if(nColumns <0) {
    		System.out.println("Error: Negative number of columns\n");
    		return;
    	}
        this.setNRows(nRows);
        this.setNColumns(nColumns);
        matrix = new Seat[nRows][nColumns];
        this.fullfilMatrix();
        this.occupiedSeats = 0;
    }

	/**
	 * Method to get the number of rows of a sitting zone
	 * 
	 * @return int with the number of rows
	 */
    public int getNRows(){
        return this.nRows;
    }

	/**
	 * Method to get the number of columns of a sitting zone
	 * 
	 * @return int with the number of columns
	 */
    public int getNColumns(){
        return this.nColumns;
    }

	/**
	 * Method to get the number of occupied seats in the zone
	 * 
	 * @return double with the number of occupied seats
	 */
	public double getOccupiedSeats(){
		return this.occupiedSeats;
	}

	/**
	 * Method to set the number of rows in a zone
	 * 
	 * @param n with the new number of rows
	 */
    public void setNRows (int n){
    	if(n <0) {
    		System.out.println("Error: Negative number\n");
    		return;
    	}
        this.nRows = n;
        return;
    }

	/**
	 * Method to set the number of columns in a zone
	 * 
	 * @param n with the new number of columns
	 */
    public void setNColumns(int n){
    	if(n <0) {
    		System.out.println("Error: Negative number\n");
    		return;
    	}
        this.nColumns = n;
        return;
    }
	
	/**
	 * Method to set the number of occupied seats
	 * 
	 * @param n with the new number of occupied seats
	 */
	public void setOccupiedSeats(double n){
    	if(n <0) {
    		System.out.println("Error: Negative number\n");
    		return;
    	}
		this.occupiedSeats=n;
	}
    
    /**
	 * Method to get the number of occupied seats
	 * 
	 * @return int with the number of attendees
	 */
	public int getAttendees() {
		return (int)occupiedSeats;
	}

	/**
	 * Method to set the occupancy of the sitting zone
	 * 
	 * @param o with new percentage of occupancy
	 */
    @Override
    public void setOccupancy(int o) {
    	if(o <0) {
    		System.out.println("Error: Negative number\n");
    		return;
    	}
    	this.resetSeatsAvailability();
    	this.occupancy = o;
        double current=(double)o/100;
        for (Seat[] sr : this.matrix){
            for (Seat s : sr){
                s.setAvailable(false);
                if(current>=1){
                    s.setAvailable(true);
                    current--;
                }
                current=current+(double)o/100;
            }
		}
    }
    
	/**
	 * Method to get the maximum number of people in the sitting zone
	 * 
	 * @return int with the maximum number of people
	 */
    @Override
    public int getNMaxPeople() {
    	return nRows*nColumns;
    }

	/**
	 * Method to get the maximum number of  possible people in the sitting zone
	 * 
	 * @return int with the possible number of people
	 */
    @Override
    public int getNPosPeople() {
    	int i = 0;
    	for(Seat sr[]: this.matrix)
    	{
    		for (Seat s: sr) 
    		{
    			if (s.getAvailable())
    			{
    				i++;
    			}
    		}
    	}
    	return i;
    }

	/**
	 * Method to reset all the seats availability
	 */
    public void resetSeatsAvailability(){
        for (Seat[] sr : this.matrix){
            for (Seat s : sr){
                s.setAvailable(true);
            }
        }
    }

	/**
	 * Method that fullfils the zone matrix with new seats
	 */
    public void fullfilMatrix(){
		for (int i = 0; i < this.nRows; i++) {
			for (int j = 0; j < this.nColumns; j++) {
				this.matrix[i][j] = new Seat(i, j);
			}
		}
    }

	/**
	 * Method that checks if a seat is available given a row and a column
	 * @param row of the seat to be checked
	 * @param column of the seat to be checked
	 * @return boolean if the seat is available
	 */
    public boolean isAvailable(int row, int column){
    	if(row >= this.getNRows()) {
    		System.out.println("Error: Row number is too large\n");
    		return false;
    	}
    	if(row >= this.getNColumns()) {
    		System.out.println("Error: Column number is too large\n");
    		return false;
    	}
		 return this.matrix[row][column].getAvailable();
    }
    
	/**
	 * Method that occupies a single seat of the zone
	 * @param seat of the zone to be occupied
	 */
    public void occupy(Seat seat) {
    	if(seat == null) {
    		System.out.println("Error: Invalid seat\n");
    		return;
    	}
    	int r = seat.getNRow();
    	int c = seat.getNColumn();
    	if(this.matrix[r][c].getAvailable()) {
    		this.matrix[r][c].setOccupied(true);
    	    this.occupiedSeats ++;
    	}
    }

	/**
	 * Method that frees a seat of the sitting zone
	 * @param seat of the zone to be freed
	 */
    public void free(Seat seat) {
    	if(seat == null) {
    		System.out.println("Error: Invalid seat\n");
    		return;
    	}
		seat.setOccupied(false);
    	this.occupiedSeats --;
    }
    
	/**
	 * Method to get a seat given a row and a column
	 * @param row of the wanted seat
	 * @param column of the wanted seat
	 * @return seat corresponded with the row and the column
	 */
    public Seat getSeat(int row, int column){
    	if(row < 0) {
    		System.out.println("Error: Negative column number\n");
    		return null;
    	}
    	if(column < 0) {
    		System.out.println("Error: Negative column number\n");
    		return null;
    	}
    	if(row >= this.getNRows()) {
    		System.out.println("Error: Row is too large\n");
    		return null;
    	}
    	if(column >= this.getNColumns()) {
    		System.out.println("Error: Column is too large\n");
    		return null;
    	}
        return matrix[row][column];
    }

	/**
	 * Method to get if a seat is occupied
	 * @param seat to be checked
	 * @return boolean if the seat is occupied
	 */
    public boolean isOccupied(Seat seat) {
    	if(seat == null) {
    		System.out.println("Error: Invalid seat\n");
    		return true;
    	}
		return seat.getOccupied();
    }

	/**
	 * Method to get the seat matrix of the sitting zone
	 * @return seat[][] matrix of the zone
	 */
    public Seat[][] getMatrix(){
        return this.matrix;
    }

	/**
	 * Method to clonate a sitting zone
	 * @return zone cloned
	 */
	@Override 
	public Zone cloneZone(){
		return new SittingZone(this.getName(), this.nRows, this.nColumns);
	}
}
