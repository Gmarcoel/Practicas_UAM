package tests;

import java.io.IOException;


import fields.*;
import forms.DataAggregator;
import forms.Form;


public class ProcessingMain {
	public static void main(String[] args) throws IOException {
		Form censusForm = new Form();
		Field<Address> adr = new Field<Address>(s -> {
			String[] data = s.split(";");
			return new Address(data[0], Integer.valueOf(data[1].trim()));
		}).addValidation(a -> a.postalCode() >= 0, "Postal code should be positive");
		Field<Integer> np = new Field<Integer>(s -> Integer.valueOf(s)).addValidation(s -> s > 0,
				"value greater than 0 expected");
		censusForm.add("Enter address and postal code separated by ';'", adr)
				.add("Number of people living in that address?", np);
		DataAggregator dag = new DataAggregator();
		for (int i = 0; i < 3; i++)
			dag.add(censusForm.exec());
		System.out.println(dag);
	}
}