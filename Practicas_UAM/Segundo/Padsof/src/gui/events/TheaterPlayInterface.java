package gui.events;

import java.awt.BorderLayout;

import javax.persistence.Column;
import javax.swing.JPanel;
import javax.swing.*;

import app.TheaterApp;
import events.Dance;
import events.Event;
import events.TheaterPlay;
import gui.mainform.MainFrame;
/**
 * This is a class that allow us to create the play interface
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class TheaterPlayInterface extends EventInterface{
	    	/**
     * Class constructor
	 * @param event event 
     * @param parent Mainframe
     * @param app theaterapp
    */
	public TheaterPlayInterface(Event event, MainFrame parent, TheaterApp app)	{
		super(event, parent, app);
	}
    	/**
     * Creates a panel for the text
	 * @param event event 
     * @param parent Mainframe
     * @param app theaterapp
	 * @return jpanel with the text
    */
	@Override
	public JPanel setText(Event event, MainFrame parent, TheaterApp app)	{
		TheaterPlay play = (TheaterPlay) event;
		JPanel container;
		container = super.setText(event, parent, app);
		JTextArea text = new JTextArea("Actors: " + play.getActors() + "\n",10,15);
		text.setEditable(false);
		text.setFont(text.getFont().deriveFont(28.0f));
		container.add(text, BorderLayout.EAST);
		return container;
	}

}
