package gui.events;

import java.awt.*;

import java.awt.event.*;

import javax.swing.*;
import app.*;
import gui.cycles.CyclesInterface;
import gui.mainform.MainFrame;
import gui.topBar.UserInterface;

/**
 * This is a class that allow us to create the tickets panel user
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class TicketsPanelUser extends JPanel{

    /**
	 * Method to create the tickets panel user
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 */
	public TicketsPanelUser (MainFrame parent, TheaterApp app){
        JPanel userPanel = new UserInterface(parent, app);
        JTabbedPane tabs = new JTabbedPane();
        JPanel ticketsPanel = new TicketsInterface(parent, app);
        JPanel cyclesPanel = new CyclesInterface(parent, app);
        tabs.addTab("Tickets", ticketsPanel);
        tabs.addTab("Passes", cyclesPanel);
        this.add(userPanel);
        this.add(tabs);
    }
    
}