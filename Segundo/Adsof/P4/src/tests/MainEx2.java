package tests;

import java.io.IOException; // Import the IOException class to handle errors
import races.*;
public class MainEx2 {
	public static void main(String[] args) {
		Race r;
		try {
			r = RaceReader.read(args[0]);
			r.simulate();
		} catch (IOException e) {
			System.out.println("Error reading the file");
		} catch (RaceException e) {
			System.out.println(e);
		}
	}
}