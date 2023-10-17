package gui.payments;

import java.awt.*;

import java.awt.event.*;

import javax.swing.*;
import app.*;
import performances.*;
import events.*;
import gui.mainform.MainFrame;
import gui.topBar.UserInterface;

/**
 * This is a class that allow us to create the pay panel
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class PayPanel extends JPanel{

    /**
	 * Method to create the pay panel
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
     * @param t ticket to be bought
	 */
	public PayPanel (MainFrame parent, TheaterApp app, Ticket t){
		this.setLayout(new GridLayout(5, 1));
        JPanel userPanel = new UserInterface(parent, app);
        this.add(userPanel);
       
        JTabbedPane tabs = new JTabbedPane();
        JPanel cardPanel = new CardPayInterface(parent, app, t);
        JPanel passPanel = new PassPayInterface(parent, app, t);
        tabs.addTab("Card", cardPanel);;
        tabs.addTab("Pass", passPanel);;
        this.add(tabs);
    } 
    
    /**
	 * Method to create the pay panel
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
     * @param p pass to pay with
	 */
	public PayPanel (MainFrame parent, TheaterApp app, Pass p){
		this.setLayout(new GridLayout(0, 1));
        JPanel userPanel = new UserInterface(parent, app);
        this.add(userPanel);
        JPanel cardPanel = new CardPayInterface(parent, app, p);
        this.add(cardPanel);
    }
    
}