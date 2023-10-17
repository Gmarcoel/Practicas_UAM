package gui.topBar;

import java.awt.*;

import java.awt.event.*;

import users.*;
import javax.swing.*;
import app.*;
import gui.events.TicketsPanelUser;
import gui.mainform.MainFrame;
import gui.mainform.MainPanel;

/**
 * This is a class that allow us to create the manage theater interface
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class UserInterface extends JPanel{

        /**
	 * Method to create the user interface
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 */
	public UserInterface (MainFrame parent, TheaterApp app){

        this.setLayout(new FlowLayout(FlowLayout.RIGHT)); // Create the layout


        int n = app.updateBookings((Customer)app.getCustomer(parent.getCurrentUser()));
        if (n!=0)
                JOptionPane.showMessageDialog(null, "You have " + n + "expired bookings");

        JButton logOut= new JButton("Log Out");
		logOut.setBackground(Color.red);
		logOut.setForeground(Color.white);
        JButton tickets= new JButton("Tickets");
		tickets.setBackground(new Color(21,45,69));
		tickets.setForeground(Color.white);
        JButton home= new JButton("Home");
		home.setBackground(new Color(21,45,69));
		home.setForeground(Color.white);
        
        
        logOut.addActionListener(e->{
                parent.setCurrentUser(null);
                parent.setLoged(false);
                parent.changeView(new MainPanel(parent, app));
        	});

        tickets.addActionListener(e->{
                parent.changeView(new TicketsPanelUser(parent, app));
        	});

        home.addActionListener(e->{
                parent.changeView(new MainPanel(parent, app));
        	});



        this.add(home);
        this.add(tickets);
        this.add(logOut);
        
        
	}
	
	
	
}
