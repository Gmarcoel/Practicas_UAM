package gui.events;

import java.awt.*;

import java.awt.event.*;

import javax.swing.*;
import app.*;
import gui.mainform.MainFrame;
import users.*;
import performances.*;

/**
 * This is a class that allow us to create the tickets interface
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class TicketsInterface extends JPanel{

	/**
	 * Method to create the ticket interface
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 */
	public TicketsInterface (MainFrame parent, TheaterApp app){
                JPanel list = new JPanel();
		
		list.setLayout(new GridLayout(0,2));
                Customer c = (Customer)app.getCustomer(parent.getCurrentUser());
                for(Ticket t : c.getTickets()){
                        list.add(new TicketButton(app, t, parent));
                }
                this.add(list);

		JScrollPane scroll = createScrollBar(list);
		this.add(scroll);
        
	}
	
	/**
	 * Method to create the scroll bar
	 * 
	 * @param son JPanel to implement the bar
	 * @return JScrollPane applied to the panel
	 */
	public static JScrollPane createScrollBar(JPanel son) {
	    JScrollPane scrollPane = new JScrollPane(son);
	    scrollPane.setPreferredSize(new Dimension(1500, 700));
	    return scrollPane;
	    
	}
	
}
