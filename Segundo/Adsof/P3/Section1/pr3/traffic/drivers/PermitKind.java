package pr3.traffic.drivers;

/**
 * This is an enum class that stores the permit kinds allong with the minimum age to aquire them
 * 
 * @author Guillermo Martin-Coello and Daniel Varela
 * 
 */
public enum PermitKind {
    A(18), B(18), C1(23);

    /**
     * This is the structure of PermitKind
     * @param min the minimum age to aquire the permit
     */
    PermitKind(int min) {
        minAge = min;
    }

    private int minAge;

    /**
     * This functio returns the minimum age to aquire a permit
     * @return the minimum age
     */
    public int getMinAge(){
        return this.minAge;
    }
}
