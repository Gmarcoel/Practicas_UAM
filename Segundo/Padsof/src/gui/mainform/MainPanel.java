package gui.mainform;

import java.awt.*;

import java.awt.event.*;

import javax.swing.*;
import app.*;
import gui.events.EventsInterface;
import gui.topBar.AdminInterface;
import gui.topBar.LoginRegisterInterface;
import gui.topBar.UserInterface;

/**
 * This is a class that allow us to create the main panel
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class MainPanel extends JPanel{

	/**
	 * Method to create the main panel with all the events
	 * 
	 * @param parent main frame
	 * @param app containing all the information of the application
	 */
	public MainPanel (MainFrame parent, TheaterApp app){
        JPanel mainPanel = new EventsInterface(parent, app);
        if(parent.getLoged()==false){
            JPanel loginRegister = new LoginRegisterInterface(parent, app);
            this.add(loginRegister);
        }
        else if(parent.getCurrentUser().equals("admin")){
            JPanel adminPanel = new AdminInterface(parent, app);
            this.add(adminPanel);
        }
        else{
            JPanel userPanel = new UserInterface(parent, app);
            this.add(userPanel);
        }
		this.setBackground(new Color(78,78,78));
        this.add(mainPanel);
    }
}