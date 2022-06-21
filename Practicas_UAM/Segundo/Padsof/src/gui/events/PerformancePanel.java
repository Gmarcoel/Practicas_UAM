package gui.events;

import java.awt.Color;
import java.awt.GridLayout;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import app.TheaterApp;
import events.Event;
import events.Pass;
import gui.mainform.MainFrame;
import gui.topBar.AdminInterface;
import performances.Performance;
import performances.Ticket;
/**
 * This is a class that allow us to create the performance panel
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class PerformancePanel extends JPanel {
	/**
	 * Constructor of the class
	 * @param p performance of the panel
	 * @param parent mainframe of the program
	 * @param app theaterapp 
	 */
	public PerformancePanel(Performance p, MainFrame parent, TheaterApp app) {
		this.setLayout(new GridLayout(0, 1));
		this.add(new AdminInterface(parent, app));
		JLabel label1 = new JLabel(p.getEventTitle()+" - "+p.getDate());
		label1.setFont(label1.getFont().deriveFont(128.0f));
		this.add(label1);

		JPanel content = new JPanel();
		content.setLayout(new GridLayout(0, 2));
		JPanel postpone = new JPanel();
		postpone.setLayout(new GridLayout(0, 1));
		JPanel cancel = new JPanel();
		cancel.setLayout(new GridLayout(0, 1));
		
		JButton cancelButton = new JButton("CANCEL PERFORMANCE");
		cancel.add(cancelButton);
		cancelButton.addActionListener(e->{
			app.cancelPerformance(p);
			JOptionPane.showMessageDialog(cancelButton, "Performance cancelled");
			parent.changeView(new EventInterface(p.getEvent(), parent, app));
		});

		JLabel newDate = new JLabel("NEW DATE: ");
		JLabel date = new JLabel("DATE: ");
		DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");
		JTextField dateField = new JTextField(p.getDate().format(dateFormatter));
		JLabel time = new JLabel("TIME: ");
		DateTimeFormatter timeFormatter = DateTimeFormatter.ofPattern("HH:mm");
		JTextField timeField = new JTextField(p.getDate().format(timeFormatter));
		JButton postponeButton = new JButton("POSTPONE PERFORMANCE");
		postponeButton.addActionListener(e->{
        	if(dateField.getText().length()!=10 || timeField.getText().length()!=5) {
        		postponeButton.setBackground(Color.RED);
    			JOptionPane.showMessageDialog(null, "Invalid date format: Date: dd/MM/yyyy Time: HH:mm");
    			return;
        		
        	}
        	else {
			try{
				DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm");
				if(app.postponePerformace(p, LocalDateTime.parse((dateField.getText()+" "+timeField.getText()), formatter))==true) {
					postponeButton.setBackground(Color.GREEN);
					JOptionPane.showMessageDialog(postponeButton, "Performance postponed");
					parent.changeView(new EventInterface(p.getEvent(), parent, app));
					return;
				}
				else {
	            	postponeButton.setBackground(Color.RED);
	    			JOptionPane.showMessageDialog(null, "Invalid date");
	    			return;
				}
			}

            catch (DateTimeParseException dtpe){
            	postponeButton.setBackground(Color.RED);
    			JOptionPane.showMessageDialog(null, "Invalid date format: Date: dd/MM/yyyy Time: HH:mm");
    			return;
            }
        	}
		});
		postpone.add(newDate);
		postpone.add(date);
		postpone.add(dateField);
		postpone.add(time);
		postpone.add(timeField);
		postpone.add(postponeButton);
		
		
		

		content.add(postpone);
		content.add(cancel);
		this.add(content);
		
		
	}

}

