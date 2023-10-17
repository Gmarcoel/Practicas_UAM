package gui.payments;

import java.awt.*;

import java.awt.event.*;
import java.util.ArrayList;

import javax.swing.*;
import app.*;
import performances.*;
import events.*;
import events.Event;
import gui.events.TicketsPanelUser;
import gui.mainform.MainFrame;
import users.*;
/**
 * This is a class that allow us to create the pay pass interface
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class PassPayInterface extends JPanel {
	Pass p = null;
	/**
	 * Method to create the pass pay interface
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 * @param t ticket to be bought
	 */
	public PassPayInterface(MainFrame parent, TheaterApp app, Ticket t) {
		JLabel pass = new JLabel("Pay with pass: "); // Create the label username
		JComboBox<String> passBox = new JComboBox<>(passesToString(parent, app, t)); // Create the textfield
		JButton payButton = new JButton("Pay");


		payButton.addActionListener(e->{
			this.p=app.getPass((String)passBox.getSelectedItem());
			if(this.p!=null){
                Customer c = (Customer)app.getCustomer(parent.getCurrentUser());
				if(app.payWithPass(c, this.p, t.getPerformance().getEvent(), t)==true){
        			payButton.setBackground(Color.GREEN);
        			JOptionPane.showMessageDialog(payButton, "Ticket purchased with pass : "+this.p.getName());
					parent.changeView(new TicketsPanelUser(parent, app));
					return;
				}
				else {

		        	payButton.setBackground(Color.BLUE);
				}
			}
        	payButton.setBackground(Color.RED);
        	JOptionPane.showMessageDialog(payButton, "Please, select a valid Pass");
		});

		this.add(pass);
		this.add(passBox);
		this.add(payButton);

	}

	/**
	 * Method to convert all the passes names to an string
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 * @param t ticket to be bought
	 * 
	 * @return Array with the names 
	 */
	public String[] passesToString(MainFrame parent, TheaterApp app, Ticket t){
		ArrayList<String> output = new ArrayList<>();
		for(Pass p : app.getValidPasses(parent.getCurrentUser(), t.getPerformance().getEvent().getTitle(), t.getZone().getName())){
			output.add(p.getName());
		}
		String s[] =new String[output.size()];
		s=output.toArray(s);
		return s;

	}
}