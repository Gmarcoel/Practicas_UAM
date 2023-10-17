package gui.cycles;

import app.TheaterApp;
import events.Cycle;
import events.*;
import events.Event;
import events.Price;
import gui.mainform.MainFrame;
import gui.mainform.MainPanel;
import gui.topBar.AdminInterface;
import gui.topBar.LoginRegisterInterface;
import gui.topBar.UserInterface;
import performances.Performance;
import zones.Zone;

import java.awt.*;
import java.util.ArrayList;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
/**
 * This is a class that allow us to create the cylce interface
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class CycleInterface extends JPanel {
	private ArrayList<Event> events = new ArrayList<>();

	/**
	 * Class constructor
	 * @param event the event for the interface
	 * @param parent Mainframe
	 * @param app Theater app
	 */
	public CycleInterface(Event event, MainFrame parent, TheaterApp app) {
		this.setLayout(new GridLayout(0, 1));
		if(parent.getLoged()==false) {
			this.add(new LoginRegisterInterface(parent, app));
			
		}
		else if (!(parent.getCurrentUser().equals("admin"))) {
			this.add(new UserInterface(parent, app));
		}

		else {		
			this.add(new AdminInterface(parent, app));
			JPanel panel = adminMode(event, parent, app); 
			this.add(panel);
			return;
		}
		JPanel container = setText(event);

		JButton button = new JButton("Back");
		button.setPreferredSize(new Dimension(80, 60));
		addListener(button, parent, app);

		JPanel subContainer = new JPanel();
		subContainer.setLayout(new BorderLayout());
		// subContainer.setPreferredSize(new Dimension(100, 150));
		subContainer.add(button, BorderLayout.EAST);
		container.add(subContainer, BorderLayout.SOUTH);
		

		this.add(container, BorderLayout.CENTER);
		
	}
	/**
	 * sets text for each cycle
	 * @param event cycle
	 * @return JPanel containing the text
	 *
	 */
	public JPanel setText(Event event) {
		Cycle cycle = (Cycle) event;
		JPanel container = new JPanel();
		container.setLayout(new BorderLayout());

		JLabel label1 = new JLabel(event.getTitle());
		label1.setFont(label1.getFont().deriveFont(128.0f));

		JTextArea text = new JTextArea("Events: ", 80, 80);
		text.setEditable(false);

		for (Event e : cycle.getEvents()) {
			text.append("\n	" + e.getTitle());
		}

		JScrollPane scroll = new JScrollPane(text, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);


	
		text.setFont(text.getFont().deriveFont(28.0f));

		container.add(label1, BorderLayout.NORTH);
		//container.add(text, BorderLayout.WEST);
	       container.add(scroll);
		container.setPreferredSize(new Dimension(1500, 700));
		return container;
	}


	/**
	 * adds a listener to the button
	 * @param button button to be listened
	 * @param parent Mainframe
	 * @param app theater app
	 */
	public static void addListener(JButton button, MainFrame parent, TheaterApp app) {
		button.addActionListener(e -> {
			button.setBackground(Color.BLUE);

			parent.changeView(new MainPanel(parent, app));

		});
	}
	
	/**
	 * adds an admin mode
	 * @param event cycle
	 * @param parent Mainframe
	 * @param app theater app
	 * @return jpanel with the admin mode
	 */
	public JPanel adminMode(Event event, MainFrame parent, TheaterApp app) {
		Cycle cycle = (Cycle) event;
		JPanel view = new JPanel();
		
		view.setLayout(new GridLayout(0, 1));
		view.setPreferredSize(new Dimension(1500, 800));
		
		JTextField name = new JTextField(event.getTitle());
		name.setFont(name.getFont().deriveFont(128.0f));

		view.add(name);
		
		JPanel eventsList = new JPanel();
		eventsList.setLayout(new FlowLayout());

		JLabel eventLabel = new JLabel("Event : ");
		JComboBox<String> dropDownEvents = new JComboBox<String>();
		JComboBox<String> dropDownInEvents = new JComboBox<String>();
		for (Event e : cycle.getEvents()) {
			this.events.add(e);
		}
		updateEventsDropDown(dropDownEvents, app);
		updateInEventsDropDown(dropDownInEvents, app);
		JButton add = new JButton("Add");
		JButton delete = new JButton("Delete");

		eventsList.add(eventLabel);
		eventsList.add(dropDownEvents);
		eventsList.add(add);
		eventsList.add(dropDownInEvents);
		eventsList.add(delete);

		view.add(eventsList);
		
		
		JPanel buttons = new JPanel();
		
		
		JButton save = new JButton("SAVE CHANGES");
		JButton deleteCycle = new JButton("DELETE CYCLE");
		buttons.add(deleteCycle);
		buttons.add(save);
		view.add(buttons);
		
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

		save.addActionListener(e->{
			cycle.changeCycle(name.getText(), this.events);
			JOptionPane.showMessageDialog(save, "Cycle "+event.getTitle()+" modified");
			parent.changeView(new MainPanel(parent, app));
		});
		
		deleteCycle.addActionListener(e->{
			app.getEvents().remove(app.getEvent(event.getTitle()));
			if(app.getPass(event.getTitle())!=null) {
				app.getPasses().remove(app.getPass(event.getTitle()));
			}
			JOptionPane.showMessageDialog(deleteCycle, "Cycle "+event.getTitle()+" deleted");
			parent.changeView(new MainPanel(parent, app));
		});

		
		
		return view;
	}
	
	/**
	 * updates dropdown
	 * @param cb combo box to check the update
	 * @param app theater app
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
	 * updates dropdown  in event
	 * @param cb combo box to check the update
	 * @param app theater app
	 */
	public void updateInEventsDropDown(JComboBox<String> cb, TheaterApp app) {
		cb.removeAllItems();
		for (Event e : this.events) {
				cb.addItem(e.getTitle());
		}
	}
}
