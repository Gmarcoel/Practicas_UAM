package gui.cycles;

import java.awt.BorderLayout;

import javax.persistence.Column;
import javax.swing.JPanel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
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
import gui.mainform.MainFrame;
import events.Cycle;
import zones.*;

/**
 * This is a class that allow us to create the main application
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class CreateCycleInterface extends JPanel {

	private ArrayList<Event> events;
	private ArrayList<Cycle> cyclesList;
	JComboBox<String> cycles = new JComboBox<String>();

	/**
	 * Method to create the cycle interface
	 * 
	 * @param parent main frame of the app
	 * @param app containing all the information of the app
	 */
	public CreateCycleInterface(MainFrame parent, TheaterApp app) {
		this.cyclesList = new ArrayList<>();
		this.events	= new ArrayList<>();
		this.setPreferredSize(new Dimension(1500, 800));
		JTabbedPane tabs = new JTabbedPane();
		tabs.addTab("Create Cycle", CreateCycle(parent, app));
		tabs.addTab("Create Cycle Pass", CreateCyclePass(parent, app));
		tabs.setBounds(50, 50, 50, 50);
		this.add(tabs);
	}

	/**
	 * Method to create the panel to work with the cycles
	 * 
	 * @param parent main frame of the app
	 * @param app containing all the information of the app
	 * @return JPanel with the panel created
	 */
	public JPanel CreateCycle(MainFrame parent, TheaterApp app) {
		JPanel cycle = new JPanel();
		cycle.setLayout(new GridLayout(0, 1));
		JPanel namePanel = new JPanel();
		JPanel eventsPanel = new JPanel();
		namePanel.setLayout(new FlowLayout(FlowLayout.LEFT));
		eventsPanel.setLayout(new FlowLayout(FlowLayout.LEFT));

		JLabel cycleLabel = new JLabel("Cycle : ");
		final JTextField cycleName = new JTextField(20);

		JLabel eventLabel = new JLabel("Event : ");
		JComboBox<String> dropDownEvents = new JComboBox<String>();
		JComboBox<String> dropDownInEvents = new JComboBox<String>();
		updateEventsDropDown(dropDownEvents, app);
		updateInEventsDropDown(dropDownInEvents, app);
		JButton add = new JButton("Add");
		JButton delete = new JButton("Delete");


		JButton create = new JButton("CREATE CYCLE");
		
		add.addActionListener(e -> {
			Event ev = app.getEvent((String) dropDownEvents.getSelectedItem());
			this.events.add(ev);
			updateInEventsDropDown(dropDownInEvents, app);
			updateEventsDropDown(dropDownEvents, app);
		});

		delete.addActionListener(e -> {
			Event ev = app.getEvent((String) dropDownInEvents.getSelectedItem());
			if (this.events.contains(ev)) {
				this.events.remove(ev);
				updateEventsDropDown(dropDownEvents, app);
				updateInEventsDropDown(dropDownInEvents, app);
			}
		});

		create.addActionListener(e->{
			app.createCycle(cycleName.getText());
			for(Event ev : this.events) {
				app.addEventToCycle(ev, (Cycle)app.getEvent(cycleName.getText()));
			}
        	JOptionPane.showMessageDialog(create, "Cycle "+cycleName.getText()+" Created");
        	this.events = new ArrayList<Event>();
			updateEventsDropDown(dropDownEvents, app);
			updateInEventsDropDown(dropDownInEvents, app);
			updateCyclesForPass(this.cycles, app);
			cycleName.setText("");
		});
		
		eventsPanel.add(eventLabel);
		eventsPanel.add(dropDownEvents);
		eventsPanel.add(add);
		eventsPanel.add(dropDownInEvents);
		eventsPanel.add(delete);

		namePanel.add(cycleLabel);
		namePanel.add(cycleName);
		
		cycle.add(namePanel);
		cycle.add(eventsPanel);
		cycle.add(create);
		return cycle;
	}

	/**
	 * Method to update the dropdown of the events
	 * 
	 * @param cb combo box to be updated
	 * @param app containing all the information of the app
	 */
	public void updateEventsDropDown(JComboBox<String> cb, TheaterApp app) {
		cb.removeAllItems();
		for (Event e : app.getEvents()) {
			if (!this.events.contains(e)) {
				cb.addItem(e.getTitle());
			}
		}
	}
	

	/**
	 * Method to update the dropdown of the events the cycle aready have
	 * 
	 * @param cb combo box to be updated
	 * @param app containing all the information of the app
	 */
	public void updateInEventsDropDown(JComboBox<String> cb, TheaterApp app) {
		cb.removeAllItems();
		for (Event e : this.events) {
				cb.addItem(e.getTitle());
		}
	}

	/**
	 * Method to create the panel of the cycle pass
	 * 
	 * @param parent main frame of the app
	 * @param app containing all the information of the app
	 * @return JPanel with the panel created
	 */
	public JPanel CreateCyclePass(MainFrame parent, TheaterApp app) {
		JPanel cyclePass = new JPanel();
		cyclePass.setLayout(new GridLayout(0, 1));

		JPanel cyclePanel = new JPanel();
		cyclePanel.setLayout(new FlowLayout(FlowLayout.LEFT));
		JPanel zonePanel = new JPanel();
		zonePanel.setLayout(new FlowLayout(FlowLayout.LEFT));
		JPanel discountPanel = new JPanel();
		discountPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
		
		
		JLabel cyclesLabel = new JLabel("Cycle : ");
		updateCyclesForPass(this.cycles, app);
		
		JLabel zoneLabel = new JLabel("Zone : ");
		JComboBox<String> zones = new JComboBox<String>();
		for(Zone z : app.getUsableZones()) {
			zones.addItem(z.getName());
		}
		
		JLabel discountLabel = new JLabel("Discount : ");
		JTextField discount = new JTextField(3);

		JButton createPass = new JButton("CREATE PASS");
		
		
		createPass.addActionListener(e->{
			app.createCyclePass((String)cycles.getSelectedItem(), Integer.parseInt(discount.getText()),app.getZone((String)zones.getSelectedItem()), (Cycle)app.getEvent((String)cycles.getSelectedItem()));
        	JOptionPane.showMessageDialog(createPass, "Cycle Pass for the cycle :"+(String)cycles.getSelectedItem()+" Created");
		});
		
		
		zonePanel.add(zoneLabel);
		zonePanel.add(zones);
		
		cyclePanel.add(cyclesLabel);
		cyclePanel.add(cycles);

		discountPanel.add(discountLabel);
		discountPanel.add(discount);

		discount.addKeyListener(new KeyAdapter(){
			public void keyTyped(KeyEvent e) {
        	char c = e.getKeyChar();
        	if (!(Character.isDigit(c) || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))) {
                getToolkit().beep();
				e.consume();
				JOptionPane.showMessageDialog(discountPanel, "Insert only numbers");
            }
         }
		});

		cyclePass.add(cyclePanel);
		cyclePass.add(zonePanel);
		cyclePass.add(discountPanel);
		cyclePass.add(createPass);
		
		return cyclePass;
	}
	
	/**
	 * Method to update the cycles of a pass
	 * 
	 * @param cb to be updated
	 * @param app containing all the information of the app
	 */
	public void updateCyclesForPass(JComboBox<String> cb, TheaterApp app) {
		cb.removeAllItems();
		for(Event e : app.getEvents()) {
			if(e instanceof Cycle) {
				cb.addItem(e.getTitle());
			}
			
		}
	}
}
