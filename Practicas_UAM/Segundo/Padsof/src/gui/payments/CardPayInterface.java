package gui.payments;

import java.awt.*;

import java.awt.event.*;

import javax.swing.*;
import app.*;
import performances.*;
import events.*;
import gui.events.TicketsPanelUser;
import gui.mainform.MainFrame;
import users.*;

/**
 * This is a class that allow us to create the main application
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class CardPayInterface extends JPanel {
	
	/**
	 * Method to create the card pay interface
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 * @param t ticket to be bought
	 */
	public CardPayInterface(MainFrame parent, TheaterApp app, Ticket t) {
		this.setLayout(new GridLayout(0, 1));
		JLabel cardNum = new JLabel("Enter card number: "); // Create the label username
		final JTextField fieldCardNum = new JTextField(10); // Create the textfield
		JPanel cardGroup = new JPanel();
		cardGroup.setLayout(new FlowLayout());
		JButton payButton = new JButton("Pay");
		JLabel price = new JLabel("Price : "+Double.toString(t.getPerformance().getEvent().getPrice(t.getZone()))+"€");
		

        cardGroup.add(cardNum);
        cardGroup.add(fieldCardNum);
        cardGroup.add(payButton);
        
        this.add(price);
        this.add(cardGroup);
        
		payButton.addActionListener(e -> {
			Customer c = (Customer) app.getCustomer(parent.getCurrentUser());
			if (app.payTicketWithCard(c, t.getPerformance().getEvent(), t, fieldCardNum.getText()) == true) {
				payButton.setBackground(Color.GREEN);
				JOptionPane.showMessageDialog(payButton, "Payment Successfull");
				parent.changeView(new TicketsPanelUser(parent, app));
			} else {
				payButton.setBackground(Color.RED);
				JOptionPane.showMessageDialog(payButton, "Payment FAILED! Check your Card number");

			}
		});
	}

	/**
	 * Method to create the card pay interface
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 * @param p pass to pay with
	 */
	public CardPayInterface(MainFrame parent, TheaterApp app, Pass p) {
		JLabel cardNum = new JLabel("Enter card number: "); // Create the label username
		final JTextField fieldCardNum = new JTextField(10); // Create the textfield
		JButton payButton = new JButton("Pay");

        this.add(cardNum);
        this.add(fieldCardNum);
        this.add(payButton);
		payButton.addActionListener(e -> {
			Customer c = (Customer) app.getCustomer(parent.getCurrentUser());
			if (app.payPassWithCard(c, p, fieldCardNum.getText()) == true) {
				payButton.setBackground(Color.GREEN);
				JOptionPane.showMessageDialog(payButton, "Payment Successfull");
				parent.changeView(new TicketsPanelUser(parent, app));
			} else {
				payButton.setBackground(Color.RED);
				JOptionPane.showMessageDialog(payButton, "Payment FAILED! Check your Card number");

			}
		});

	}
}