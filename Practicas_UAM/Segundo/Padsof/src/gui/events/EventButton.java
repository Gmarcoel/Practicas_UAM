package gui.events;

import java.awt.*;

import java.awt.event.*;

import javax.swing.*;
import app.*;

/**
 * This is a class that allow us to create the event butrton
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class EventButton extends JButton{

	/**
     * Class constructor
	 * @param event name
     * @param author name
	 * @param duration integer
    */
	public EventButton(String event, String author, int duration) {
		JButton button = new JButton();
		button.setLayout(new BorderLayout());
		JLabel label1 = new JLabel(event);
		label1.setFont(label1.getFont().deriveFont(64.0f));
		JLabel label2 = new JLabel("Author: " + author);
		label2.setFont(label1.getFont().deriveFont(14.0f));
		JLabel label3 = new JLabel("Durantion: " + duration + " minutes");
		label3.setFont(label1.getFont().deriveFont(14.0f));
		JPanel sub = new JPanel(new BorderLayout());

		sub.add(label2,BorderLayout.NORTH);
		sub.add(label3,BorderLayout.SOUTH);

		button.add(BorderLayout.NORTH,label1);
		button.add(BorderLayout.SOUTH,sub);
	}
}