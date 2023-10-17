package gui.events;


import java.awt.*;


import java.awt.event.*;

import javax.swing.*;
import app.*;
import gui.mainform.MainFrame;
import gui.payments.PayPanel;
import performances.*;
import zones.*;

/**
 * This is a class that allow us to create the ticket button
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class TicketButton extends JButton{
    	/**
     * Creates a ticket button
	 * @param app theater app 
     * @param t ticket
     * @param parent mainframe
    */
	public TicketButton(TheaterApp app, Ticket t, MainFrame parent) {
		this.setLayout(new BorderLayout());
		JPanel sub = new JPanel();
		sub.setLayout(new GridLayout(0, 2));
		JLabel label1 = new JLabel(t.getPerformance().getEventTitle());
		label1.setFont(label1.getFont().deriveFont(64.0f));
		JLabel label2 = new JLabel("Author: " + t.getPerformance().getEvent().getAuthor());
		label2.setFont(label2.getFont().deriveFont(14.0f));
		JLabel label3 = new JLabel("Durantion: " + t.getPerformance().getEvent().getDuration() + " minutes");
		label3.setFont(label3.getFont().deriveFont(14.0f));
		JLabel label4 = new JLabel("Zone: " + t.getZone().getName());
		label4.setFont(label4.getFont().deriveFont(14.0f));
		sub.add(label2);
		sub.add(label3);
		sub.add(label4);
		
		if(t.getZone() instanceof SittingZone) {

			JLabel label5 = new JLabel("Seat: C: " + t.getSeat().getNColumn()+" R: "+ t.getSeat().getNRow());
			label5.setFont(label5.getFont().deriveFont(14.0f));
			sub.add(label5);
			
		}
		
		JLabel label6 = new JLabel("Date: " + t.getPerformance().getDate());
		label6.setFont(label6.getFont().deriveFont(14.0f));


		sub.add(label6);


		if(t.getPurchased()==true){
			JLabel label7 = new JLabel("Purchased");
			label7.setFont(label7.getFont().deriveFont(14.0f));
			JButton download = new JButton("Download");
			this.add(BorderLayout.CENTER, label7);
			this.add(BorderLayout.CENTER, download);
        	download.addActionListener(e->{
                t.generateTicketPDF();
        		});
		}
		else{
			JLabel label8 = new JLabel("Booked");
			label8.setFont(label8.getFont().deriveFont(14.0f));
			JButton purchase = new JButton("Purchase");
			this.add(BorderLayout.CENTER, label8);
			this.add(BorderLayout.CENTER, purchase);
        	purchase.addActionListener(e->{
                parent.changeView(new PayPanel(parent, app, t));
        		});
		}

		this.add(BorderLayout.NORTH,label1);
		this.add(BorderLayout.SOUTH,sub);
		this.addActionListener(e->{
			parent.changeView(new EventInterface(t.getPerformance().getEvent(), parent, app));
		});

	}
}