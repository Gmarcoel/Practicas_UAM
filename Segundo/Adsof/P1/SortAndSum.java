
import java.util.SortedSet;
import java.util.TreeSet;

/**
 * This class keeps ordered a set of integer numbers and divides them between odd or even
 * 
 * @author Daniel & Guillermo
 */

public class SortAndSum {
    
    private SortedSet<Integer> OddNumbers= new TreeSet<>();
    private SortedSet<Integer> EvenNumbers= new TreeSet<>();
    private SortedSet<Integer> numbers= new TreeSet<>();
    int evenSum=0;
    int oddSum=0;
    int totalSum=0;


    
    /**
     * Constructor, with the array of strings
     * @param params strings to insert, after converting them to numbers
     */
    public SortAndSum(String ... params){
        for (String s: params){ 		//we traverse the array
            int n= Integer.parseInt(s); 
            if(n%2==0){
                  EvenNumbers.add(n);   
            } else{
                OddNumbers.add(n); 
            }			//add to set
        }

    }
    /**
     * @return numbers
     */
    public SortedSet<Integer> getNumbers(){
        return numbers;
    }
    /**
     * @return the number of numbers in the collection 
     */
    public int getTotalNumbers() {
    	return this.numbers.size();
    }

    /**
     *
     * @return String representing this object
     */
    public String toString(){
        return "Even numbers " + this.EvenNumbers.toString() + " (sum: " + this.getEvenSum() + ")\nOdd numbers " + this.OddNumbers.toString() + " (sum: "+ this.getOddSum() + ")\n";	// print the set
    }

    /**
     * @return the sum of the even numbers
     */
    public int getEvenSum(){
        evenSum=0;
        for (int n:EvenNumbers){
            evenSum=evenSum+n;
        }
        return evenSum;
    }
    
    /**
     * @return the sum of the odd numbers
     */
    public int getOddSum(){
        oddSum=0;
        for (int n:OddNumbers){
            oddSum=oddSum+n;
        }
        return oddSum;
    }
        
    
    /**
     * @param param
     * @brief adds the parameter to the corresponding even or odd group
     */
    public void add(int param){
        if(param%2==0){
            this.EvenNumbers.add(param);
        }else{
            this.OddNumbers.add(param);
        }

    }
        

    /**
     * Application entry point.
     *
     * This method orders the numbers of the command line, adds two values and distributes all the numbers in odd or even
     * @param args The arguments of the command line: should be at least two numbers
     */
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("At least two numbers are expected");
            System.out.println("Returns the ordered even and odd numbers without repetition and their sum");
        } else {
            SortAndSum c = new SortAndSum(args);
            System.out.println(c); // We print the sorted sets and their sum, through the console
            c.add(30); // method to add a number
            c.add(33); // Add number 33
            System.out.println(c); // We print the sorted sets and their sum
            System.out.println("Sum even numbers: " + c.getEvenSum()); // We print the sum even numbers
            System.out.println("Sum odd numbers: " + c.getOddSum()); // We print the sum odd numbers
            System.out.println("Total sum: " + (c.getEvenSum() + c.getOddSum())); // total sum
        }
    }

}