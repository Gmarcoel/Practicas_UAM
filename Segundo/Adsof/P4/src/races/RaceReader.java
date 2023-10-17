package races;

import java.io.File; // Import the File class
import java.io.IOException;
import java.util.HashSet;
import java.util.Scanner; // Import the Scanner class to read text files

import vehicles.Car;
import vehicles.IVehicle;
import vehicles.Motorcycle;
import vehicles.Truck;
import components.*;

/**
 * Reads the race information through input
 * 
 * @author Daniel Varela & Guillermo Martín-Coello
 *
 */
public class RaceReader {
	/**
	 * Reads the file input and creates the race
	 * 
	 * @param file file to be read
	 * @return created race
	 * @throws RaceException race exception
	 * @throws IOException   input exception
	 */
	public static Race read(String file) throws RaceException, IOException {
		// try {
		File f = new File(file);
		Scanner s = new Scanner(f);

		int lenght = 0;
		int number;
		String className;
		double mSpeed;
		IVehicle v;

		if (s.hasNextLine()) {
			lenght = Integer.parseInt(s.nextLine()); // Length of race
		}

		Race race = new Race(lenght);
		while (s.hasNextLine()) {
			number = Integer.parseInt(s.next()); // Vehicle type
			className = s.next();
			mSpeed = Double.parseDouble(s.next()); // Vehicle speed
			HashSet<String> componentNames = new HashSet<>();
			while (s.hasNext("Wheels") || s.hasNext("Engine") || s.hasNext("Window") || s.hasNext("BananaDispenser")) {
				componentNames.add(s.next()); // Adds all the component names to a hash set
			}

			for (int i = 0; i < number; i++) {
				if (className.compareTo("Truck") == 0) {
					v = new Truck(mSpeed);
				} else if (className.compareTo("Motorcycle") == 0) {
					v = new Motorcycle(mSpeed);

				} else {
					v = new Car(mSpeed);
				}
				// Adding component
				for (String c : componentNames) {
					try {
						if (c.equals("Wheels")) {
							v.addComponent(new Component("Wheels", 3, true, v));
						}
						if (c.equals("Engine")) {
							v.addComponent(new Component("Engine", 3, true, v));
						}
						if (c.equals("Window")) {
							v.addComponent(new Component("Window", 2, false, v));
						}
						if (c.equals("BananaDispenser")) {
							v.addComponent(new Component("BananaDispenser", 4, false, v));
						}
					} catch (InvalidComponentException e) {
						System.out.println("Component " + c + " is not valid for vehicle " + v.getName());
						s.close();
						throw new RaceException();
					}
				}

				race.addVehicle(v);

			}
		}

		s.close();
		if (race.checkViability() == false) {
			throw new RaceException();
		}
		return race;
		/*
		 * } catch (IOException e) { System.out.println("An error occurred.");
		 * e.printStackTrace();
		 * 
		 * throw new RaceException();
		 */
	}

}