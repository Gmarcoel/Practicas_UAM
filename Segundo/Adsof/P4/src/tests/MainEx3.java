package tests;

import java.io.IOException; // Import the IOException class to handle errors

import races.*;
public class MainEx3 {
	public static void main(String[] args) {
		Race r;
		try {
			r = RaceReader.read(args[0]);
			r.allowAttacks(true);
			r.simulate();
		} catch (IOException e) {
			System.out.println("Error reading the file");
		} catch (RaceException e) {
			System.out.println(e);
		}
	}
}
