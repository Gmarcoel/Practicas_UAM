package gui.cycles;

import java.awt.*;

import java.awt.event.*;
import java.time.LocalDate;
import java.time.LocalDateTime;

import javax.swing.*;
import app.*;
import events.*;
import events.Event;
import gui.mainform.MainFrame;
import gui.passes.PassInterface;
import users.*;

/**
 * This is a class that allow us to create the cycle buttons
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class CycleButton extends JButton{

	/**
	 * Class constructor
	 * @param app Theater app
	 * @param parent Mainframe
	 * @param p the pass for the interface
	 */
	public CycleButton(TheaterApp app, MainFrame parent, Pass p) {
		this.setLayout(new BorderLayout());
		JLabel label1 = new JLabel(p.getName());
		label1.setFont(label1.getFont().deriveFont(64.0f));
		this.addActionListener(e->{
			parent.changeView(new PassInterface(p, parent, app));
		});
		this.add(BorderLayout.NORTH,label1);
	}

	/**
	* Constructor of the class
	* @param app theater app
	* @param parent mainframe
	* @param p pass
	* @param c customer
	*/
	public CycleButton(TheaterApp app, MainFrame parent, Pass p, Customer c) {
		this.setLayout(new GridLayout(0,1));
		JLabel label1 = new JLabel(p.getName());
		label1.setFont(label1.getFont().deriveFont(64.0f));
		this.add(label1);
		JLabel label2 = new JLabel("Zone : "+p.getZone().getName());
		this.add(label2);
		if(p instanceof CyclePass){
		this.add(new JLabel("You can attend:"));
		for(Event e : ((CyclePass)p).getCanGoToList()){
			this.add(new JLabel(e.getTitle()));
		}
		this.addActionListener(e->{
			parent.changeView(new PassInterface(p, parent, app));
		});
		}
		else {
			LocalDate t = ((AnnualPass)p).getEndDate();
			this.add(new JLabel("Valid until :"+ t));
			this.addActionListener(e->{
				parent.changeView(new PassInterface(parent, app));
			});
			
		}
			this.add(new JLabel("You have already attended:"));
		for(Event e : p.getAlreadyAttendedList()){
			this.add(new JLabel(e.getTitle()));
		}
	}

	
}