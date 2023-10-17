package gui.events;

import java.awt.BorderLayout;

import javax.persistence.Column;
import javax.swing.JPanel;
import javax.swing.*;


import java.awt.*;
import java.lang.Integer;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;
import java.awt.event.*;

import javax.swing.*;

import java.time.*;
import java.time.format.DateTimeFormatter;

import app.TheaterApp;
import events.Concert;
import events.Dance;
import events.Event;
import events.Price;
<<<<<<< HEAD:src/gui/events/CreateEventInterface.java
import gui.mainform.MainFrame;
import gui.mainform.MainPanel;
import zones.Zone;
/**
 * This is a class that allow us to create the event interface
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
=======
import zones.Zone;

>>>>>>> 1cd9b5ca3eae2f21b66106514195f08a9f18320b:src/gui/mainform/CreateEventInterface.java
public class CreateEventInterface extends JPanel {

        private final JTextField titleField = new JTextField(30); // Create the textfield
        private final JTextField authorField = new JTextField(30); // Create the textfield
        private final JTextField directorField = new JTextField(30); // Create the textfield
        private final JTextField priceField = new JTextField(7); // Create the textfield
        private final JTextArea descriptionField = new JTextArea(3, 2); // Create the textfield
        private final JTextField durationField = new JTextField(5); // Create the textfield
        private Set<LocalDateTime> performancesTimes = new HashSet<LocalDateTime>(); // Create the textfield
        private ArrayList<Price> prices = new ArrayList<>();
<<<<<<< HEAD:src/gui/events/CreateEventInterface.java
    /**
     * Class constructor
     * @param parent Mainframe
     * @param app theaterapp
    */
=======

>>>>>>> 1cd9b5ca3eae2f21b66106514195f08a9f18320b:src/gui/mainform/CreateEventInterface.java
	public CreateEventInterface(MainFrame parent, TheaterApp app){
		this.setPreferredSize(new Dimension (1500, 800));
        this.setLayout(new GridLayout(0, 2));
        JTabbedPane tabs = new JTabbedPane();
        descriptionField.setLineWrap(true);
        tabs.addTab("Theater Play", theaterPlaySpecifics(parent, app));
        tabs.addTab("Dance", danceSpecifics(parent, app));
        tabs.addTab("Concert", concertSpecifics(parent, app));
		tabs.setBounds(50, 50, 50, 50);
        this.add(commonPart(app));
        this.add(tabs);
    }

    /**
     * creates the panel for performances
     * @return JPanel with the performance
     */
    public JPanel createPerformancePanel(){
        JPanel performanceCreate = new JPanel();
        performanceCreate.setLayout(new FlowLayout(FlowLayout.LEFT));
        //Creating a performance pannel
        JLabel date = new JLabel("Date : "); 
        final JTextField dateField = new JTextField(7); 
        JLabel time = new JLabel("Time : ");
        final JTextField timeField = new JTextField(7);  
        JButton addPerformance = new JButton("+");
        JComboBox<String> dates = new JComboBox<>();
        
        addPerformance.addActionListener(e->{
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm");
            String recieved = dateField.getText()+" "+timeField.getText(); 
            LocalDateTime dateTime = LocalDateTime.parse(recieved, formatter);
            if(this.performancesTimes.add(dateTime)==true){
        		addPerformance.setBackground(Color.GREEN);
                dates.addItem(formatter.format(dateTime));
        	    JOptionPane.showMessageDialog(addPerformance, "Performance added on :"+dateField.getText()+" at "+timeField.getText());
            }
            else{
        		addPerformance.setBackground(Color.RED);
        	    JOptionPane.showMessageDialog(addPerformance, "Unable to create performance on :"+dateField.getText()+" at "+timeField.getText()+" because it already exists");
            }
        });

        performanceCreate.add(date);
        performanceCreate.add(dateField);
        performanceCreate.add(time);
        performanceCreate.add(timeField);
        performanceCreate.add(addPerformance);
        performanceCreate.add(dates);
        return performanceCreate;
    }


<<<<<<< HEAD:src/gui/events/CreateEventInterface.java
    /**
     * creates a panel for the common part
     * @param app theaterapp
     * @return a panel with the content
    */
=======
    
>>>>>>> 1cd9b5ca3eae2f21b66106514195f08a9f18320b:src/gui/mainform/CreateEventInterface.java
    public JPanel commonPart(TheaterApp app){
        JPanel commonPart = new JPanel();
        commonPart.setLayout(new GridLayout(0, 1));
        //commonPart.setLayout(new BorderLayout());
        
        JLabel title = new JLabel("Title: "); 
        JLabel author = new JLabel("Author: "); 
        JLabel director = new JLabel("Director : "); 
        JPanel pricePan = new JPanel();
        JLabel price = new JLabel("Price : ");
        JComboBox<String> zones = new JComboBox<String>();
        for(Zone z : app.getUsableZones()) {
        	zones.addItem(z.getName());
        }
        JButton addZonePrice =new JButton("Add price");
        pricePan.setLayout(new FlowLayout());
        pricePan.add(price);
        pricePan.add(zones);
        pricePan.add(this.priceField);
        pricePan.add(addZonePrice);
        
        zones.addActionListener(e->{
        	for(Price p : this.prices) {
        		if(p.getZone()==app.getZone((String)zones.getSelectedItem())) {
        			this.priceField.setText(Double.toString(p.getPrice()));
        			addZonePrice.setBackground(Color.GREEN);
        			return;
        		}
        	}
        	this.priceField.setText("");
			addZonePrice.setBackground(Color.GRAY);
        });
        
        addZonePrice.addActionListener(e->{
        	try
        	{
        	  Double.parseDouble(this.priceField.getText());
        	}
        	catch(NumberFormatException nfe)
        	{
        	    JOptionPane.showMessageDialog(addZonePrice, "Price not valid");
    			addZonePrice.setBackground(Color.RED);
    			return;
        	}
        	if(this.prices.add(new Price(app.getZone((String)zones.getSelectedItem()), Double.parseDouble(this.priceField.getText())))) {
        		addZonePrice.setBackground(Color.GREEN);
        		return;
        	}
    	    JOptionPane.showMessageDialog(addZonePrice, "Price not valid");
			addZonePrice.setBackground(Color.RED);
        	
        });
        
        JLabel description = new JLabel("Description : ");
        JLabel duration = new JLabel("Duration : "); 
        commonPart.add(title);
        commonPart.add(this.titleField);
        commonPart.add(author);
        commonPart.add(this.authorField);
        commonPart.add(director);
        commonPart.add(this.directorField);
        commonPart.add(pricePan);
        commonPart.add(description);
        commonPart.add(this.descriptionField);
        commonPart.add(duration);
        commonPart.add(this.durationField);
        commonPart.add(createPerformancePanel());
        return commonPart;
    }

    /**
     * Create the specific for theater play
     * @param parent mainframe
     * @param app theater app
     * @return a panel with the content
    */
    public  JPanel theaterPlaySpecifics(MainFrame parent, TheaterApp app){
        JPanel theaterPlay = new JPanel();
        theaterPlay.setLayout(new GridLayout(0, 1));
        JLabel actors = new JLabel("Actors : ");
        final JTextField actorsField = new JTextField(50);
        theaterPlay.add(actors);
        theaterPlay.add(actorsField);
        
        JButton create = new JButton("CREATE EVENT");

        create.addActionListener(e->{
            app.createPlayEvent(this.titleField.getText(), this.authorField.getText(), this.directorField.getText(), this.descriptionField.getText(), actorsField.getText(), Integer.parseInt(this.durationField.getText()));
            
            for(Price p : this.prices) {
            	app.getEvent(this.titleField.getText()).setPrice(p.getZone(), p.getPrice());
            }
            for(LocalDateTime t : this.performancesTimes){
                app.createPerformance(app.getEvent(this.titleField.getText()), t);
            }
        	JOptionPane.showMessageDialog(create, "Event created");
            parent.changeView(new MainPanel(parent, app));
        });

        theaterPlay.add(create);
        return theaterPlay;
    }

    /**
     * Create the specific for dance
     * @param parent mainframe
     * @param app theater app
     * @return a panel with the content
    */
    public  JPanel danceSpecifics(MainFrame parent, TheaterApp app){
        JPanel dance = new JPanel();
        dance.setLayout(new GridLayout(0, 1));
        JLabel orchestra = new JLabel("Orchestra : ");
        final JTextField orchestraField = new JTextField(30);
        JLabel conductor = new JLabel("Conductor : ");
        final JTextField conductorField = new JTextField(30);
        JLabel dancers = new JLabel("Dancers : ");			
        final JTextField dancersField = new JTextField(30);

        JButton create = new JButton("CREATE EVENT");

        create.addActionListener(e->{
            app.createDanceEvent(this.titleField.getText(), this.authorField.getText(), this.directorField.getText(), this.descriptionField.getText(), conductorField.getText(), dancersField.getText(), orchestraField.getText(), Integer.parseInt(this.durationField.getText()));
        	
            for(Price p : this.prices) {
            	app.getEvent(this.titleField.getText()).setPrice(p.getZone(), p.getPrice());
            }
            for(LocalDateTime t : this.performancesTimes){
                app.createPerformance(app.getEvent(this.titleField.getText()), t);
            }
            JOptionPane.showMessageDialog(create, "Event created");
            parent.changeView(new MainPanel(parent, app));
        });
        
        dance.add(orchestra);
        dance.add(orchestraField);
        dance.add(conductor);
        dance.add(conductorField);
        dance.add(dancers);
        dance.add(dancersField);
        dance.add(create);
        return dance;
    }
    /**
     * Create the specific for concert
     * @param parent mainframe
     * @param app theater app
     * @return a panel with the content
    */
    public  JPanel concertSpecifics(MainFrame parent, TheaterApp app){
        JPanel concert = new JPanel();
        concert.setLayout(new GridLayout(0, 1));
        JLabel orchestra = new JLabel("Orchestra : ");
        final JTextField orchestraField = new JTextField(40);
        JLabel pieces = new JLabel("Music pieces : ");
        final JTextField piecesField = new JTextField(50);
        JButton create = new JButton("CREATE EVENT");

        create.addActionListener(e->{
            app.createConcertEvent(this.titleField.getText(), this.authorField.getText(), this.directorField.getText(), this.descriptionField.getText(), piecesField.getText(), orchestraField.getText(), Integer.parseInt(this.durationField.getText()));
        	
            for(Price p : this.prices) {
            	app.getEvent(this.titleField.getText()).setPrice(p.getZone(), p.getPrice());
            }
            for(LocalDateTime t : this.performancesTimes){
                app.createPerformance(app.getEvent(this.titleField.getText()), t);
            }
            JOptionPane.showMessageDialog(create, "Event created");
            parent.changeView(new MainPanel(parent, app));
        });

        concert.add(orchestra);
        concert.add(orchestraField);
        concert.add(pieces);
        concert.add(piecesField);
        concert.add(create);
        return concert;
    }

    

}
