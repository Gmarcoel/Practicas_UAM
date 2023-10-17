package tests;

import java.io.IOException;
import java.util.Scanner;

import races.Race;
import races.RaceException;
import races.RaceReader;

public class MainTest {
	public static void main(String [] args) {
       /**
       * In this test we create a race with 1 car, 1 truck and 1 motorcycle. All with the same velocity.
       * There are no attacks and no power-ups, hence the fastest vehicle should always win. This should 
       * be the motorcycle because it's always going to max speed, then the car who has a 90% of probability of 
       * going to max speed and a 10% of going to 90% of its speed, and then the truck which has a 90% of chance 
       * of going at max speed and a 10% of going at 80% of its max speed. In order for this to be true we need 
       * a race with several turns so the case where the car goes at 90% of its speed and the truck at 80% happen.
       */
        Race r;
         try {
            r = RaceReader.read("src/tests/inputs/inputT1.txt");
            r.simulate();
         } catch (IOException e) {
            System.out.println("Error reading the file");
         } catch (RaceException e) {
            System.out.println(e);
         }
         System.out.println("Press \"ENTER\" to continue with race 2...");
         Scanner scanner = new Scanner(System.in);
         scanner.nextLine();
        System.out.println("--------------------------------------------------------------");
      /**
      * This race will allow attacks, here the motorcycle looses its advantage because it can't have a banana 
      * dispenser so the expected outputoutcome for this race should be for the car to win unless it's hit on a 
      * critical part. This race will be more equilibrated unless one of the vehicles gets a 30 meter advantage 
      * from the others hence exitting the range of attack without getting hit on any critical part. There is a 50% 
      * chance of hitting the attack and another 50 of failing.
      */
 		Race r2;
 		try {
 			r2 = RaceReader.read("src/tests/inputs/inputT2.txt");
 			r2.allowAttacks(true);
 			r2.simulate();
 		} catch (IOException e) {
 			System.out.println("Error reading the file");
 		} catch (RaceException e) {
 			System.out.println(e);
 		}
       
         System.out.println("Press \"ENTER\" to continue with race 3...");
         scanner.nextLine();
         System.out.println("--------------------------------------------------------------");
 		/**
 		 * This race will not allow attacks, but instead it will allow power ups. This could help the slower vehicles to have a chance to win the
 		 * faster ones, but not as much as with attacks. It is long enough that is very probable that they use power ups at least once.
 		 * The most probable winner of the race should be a motorcycle.
 		 */
        Race r3;
        try {
        r3 = RaceReader.read("src/tests/inputs/inputT3.txt");
        r3.allowPowerUps(true);
        r3.simulate();
        } catch (IOException e) {
            System.out.println("Error reading the file");
        } catch (RaceException e) {
            System.out.println(e);
        }
        
        System.out.println("Press \"ENTER\" to continue with race 4...");
        scanner.nextLine();
        System.out.println("--------------------------------------------------------------");
 		
        /**
         * This is a complete race with both attacks and power ups allowed. This should be a very
         * balanced race where any vehicle has chances to win.
         */
        Race r4;
        try {
        r4 = RaceReader.read("src/tests/inputs/inputT4.txt");
        r4.allowAttacks(true);
        r4.allowPowerUps(true);
        r4.simulate();
        } catch (IOException e) {
            System.out.println("Error reading the file");
        } catch (RaceException e) {
            System.out.println(e);
        }
        System.out.println("Press \"ENTER\" to continue with race 5...");
        scanner.nextLine();
        System.out.println("--------------------------------------------------------------");
        /* This is a long race. It should take a lot of turns but everything should run smoothly*/
        Race r5;
        try {
        r5 = RaceReader.read("src/tests/inputs/inputT5.txt");
        r5.allowAttacks(true);
        r5.allowPowerUps(true);
        r5.simulate();
        } catch (IOException e) {
            System.out.println("Error reading the file");
        } catch (RaceException e) {
            System.out.println(e);
        }
        
        System.out.println("Press \"ENTER\" to continue with race 6...");
        scanner.nextLine();
        System.out.println("--------------------------------------------------------------");
        
        /**
         *  This race should not work because the number of vehicles is too high
         *  It should cause a race exception error
         */
        Race r6;
        try {
        r6 = RaceReader.read("src/tests/inputs/inputT6.txt");
        r6.allowAttacks(true);
        r6.allowPowerUps(true);
        r6.simulate();
        } catch (IOException e) {
            System.out.println("Error reading the file");
        } catch (RaceException e) {
            System.out.println(e);
        }
        
        
        System.out.println("Press \"ENTER\" to continue with race 7...");
        scanner.nextLine();
        System.out.println("--------------------------------------------------------------");
        /**
         *  This race should not work because the velocity of a vehicle is larger than the race length
         *  It should cause a race exception error
         */
        Race r7;
        try {
        r7 = RaceReader.read("src/tests/inputs/inputT7.txt");
        r7.allowAttacks(true);
        r7.allowPowerUps(true);
        r7.simulate();
        } catch (IOException e) {
            System.out.println("Error reading the file");
        } catch (RaceException e) {
            System.out.println(e);
        }
        
        System.out.println("Press \"ENTER\" to continue with race 8...");
        scanner.nextLine();
        
        System.out.println("--------------------------------------------------------------");
        /**
         *  This race should not work because the motorcycle recieves an invalid component
         *  It should cause a race exception error
         */
        Race r8;
        try {
        r8 = RaceReader.read("src/tests/inputs/inputT8.txt");
        r8.allowAttacks(true);
        r8.allowPowerUps(true);
        r8.simulate();
        } catch (IOException e) {
            System.out.println("Error reading the file");
        } catch (RaceException e) {
            System.out.println(e);
        }
        
        scanner.close();
        
        System.out.println("--------------------------------------------------------------");
        System.out.println("--------------------------------------------------------------");
        System.out.println("End of the tests");
	}
	
	
	
	
}
