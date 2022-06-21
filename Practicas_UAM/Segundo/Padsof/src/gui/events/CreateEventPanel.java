package gui.events;

import java.awt.BorderLayout;

import javax.persistence.Column;
import javax.swing.JPanel;
import javax.swing.*;

import app.TheaterApp;
import events.Concert;
import events.Dance;
import events.Event;
import gui.mainform.MainFrame;
import gui.topBar.AdminInterface;
/**
 * This is a class that allow us to create the event panel
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class CreateEventPanel extends JPanel {
    /**
     * Class constructor
     * @param parent Mainframe
     * @param app theaterapp
    */
	public CreateEventPanel(MainFrame parent, TheaterApp app){
        JPanel adminInterface = new AdminInterface(parent, app);
        JPanel createEvent = new CreateEventInterface(parent, app);
        this.add(adminInterface);
        this.add(createEvent);
    }
}