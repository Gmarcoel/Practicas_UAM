package gui.events;

import java.awt.*;

import javax.swing.*;
import app.TheaterApp;
import events.*;
import events.Event;
import gui.cycles.CycleInterface;
import gui.mainform.MainFrame;
import gui.passes.PassInterface;
import events.AnnualPass;

/**
 * This is a class that allow us to create the main application
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class EventsInterface extends JPanel{

	/**
	 * Method to create events interface
	 * 
	 * @param parent main frame of the app
	 * @param app containing all the information of the app
	 */
	public EventsInterface(MainFrame parent, TheaterApp app) {
		this.setBackground(new Color(78,78,78));
		// Create a panel for each tab
		JPanel tab1= new JPanel();
		//tab1.setPreferredSize(new Dimension(1000, 1000));
		// Two other panels
		JPanel tab2= new JPanel();
		tab2.setSize(new Dimension(600, 600));
		JPanel tab3= new JPanel();
		JPanel tab4= new JPanel();
		JPanel tab5= new JPanel();
		JPanel tab6= new JPanel();
		// Crate a container of type JTabbedPane (not a JPanel). 
		eventList(tab1, app, 1, parent);
		eventList(tab2, app, 2, parent);
		eventList(tab3, app, 3, parent);
		eventList(tab4, app, 4, parent);
		eventList(tab5, app, 5, parent);
		eventList(tab6, app, 6, parent);
		
		JTabbedPane tabs= new JTabbedPane();
		tabs.setBackground(new Color(153,0,26));
		tabs.setForeground(Color.white);
		tabs.setBounds(50, 50, 50, 50);
		this.add(tabs);
		// Add panels to container using the method addTab(<title>,<panel>)
		tabs.addTab("Theater", tab1);
		tabs.addTab("Concert", tab2);
		tabs.addTab("Dance", tab3);
		tabs.addTab("Cycles", tab4);
		tabs.addTab("Passes", tab5);
		tabs.addTab("All", tab6);
		/*
		parent.setSize(1200,1200);
		parent.setVisible(true);
		parent.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		*/
	}
	
	/**
	 * Method to update the info of the panel
	 * 
	 * @param container main panel of the events
	 * @param app containing all the information of the app
	 * @param type number to search the events
	 * @param parent main frame of the app
	 */
	public static void eventList(JPanel container, TheaterApp app, int type, MainFrame parent) {
		
		JPanel list = new JPanel();
		list.setBackground(new Color(154,154,154));
		
		list.setLayout(new GridLayout(0,2));
		JButton button;
		
		for (Event e : app.getEvents())	{
			button = null;
			if ((e instanceof TheaterPlay)&& (type == 1)) {
				list.add(button = eventButtonCreator(e.getTitle(),e.getAuthor(), e.getDuration()));
			}
			if ((e instanceof Concert)&& (type == 2)) {
				list.add(button = eventButtonCreator(e.getTitle(),e.getAuthor(), e.getDuration()));	
			}
			if ((e instanceof Dance)&& (type == 3)) {
				list.add(button = eventButtonCreator(e.getTitle(),e.getAuthor(), e.getDuration()));
			}
			
			if ((e instanceof Cycle)&&(type == 4)) {
				list.add(button = eventCycleCreator(e.getTitle()));	
			}

			if ((e instanceof Cycle)&& (type == 6)) {
				list.add(button = eventCycleCreator(e.getTitle()));	
			}
			if ((!(e instanceof Cycle))&& (type == 6)) {
				list.add(button = eventButtonCreator(e.getTitle(),e.getAuthor(), e.getDuration()));
			}
			if(button!= null)
				addListener(button, e, parent, app);
		}
		if(type==5 || type==6) {
			for(Pass p : app.getPasses()) {
				button=null;
				list.add(button = eventPassCreator(p.getName()));
				addListener(button, p, parent, app);
			}
			list.add(button = eventPassCreator("Annual Pass"));
			addListener(button, parent, app);
		}
		


		JScrollPane scroll = createScrollBar(list);
		container.add(scroll);
		
	}

	/**
	 * Method to create a button for the events
	 * 
	 * @param event string with the name of the event
	 * @param author of the event
	 * @param duration of the event
	 * @return JButton created
	 */
	public static JButton eventButtonCreator(String event, String author, int duration) {
		JButton button = new JButton();
		button.setBackground(new Color(204,204,204));
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
		return button;
	}

	/**
	 * Method to create a button for the cycle creator
	 * 
	 * @param cycle to implement the button
	 * @return JButton created
	 */
	public static JButton eventCycleCreator(String cycle) {
		JButton button = new JButton();
		button.setBackground(new Color(204,204,204));
		button.setLayout(new BorderLayout());
		JLabel label1 = new JLabel("Cycle "+cycle);
		label1.setFont(label1.getFont().deriveFont(64.0f));
		button.add(BorderLayout.NORTH,label1);

		return button;

	}

	/**
	 * Method to create a button for the cycle pass
	 * 
	 * @param cycle with the cycle pass
	 * @return JButton created
	 */
	public static JButton eventPassCreator(String cycle) {
		JButton button = new JButton();
		button.setBackground(new Color(204,204,204));
		button.setLayout(new BorderLayout());
		JLabel label1 = new JLabel("Pass : "+cycle);
		label1.setFont(label1.getFont().deriveFont(64.0f));
		button.add(BorderLayout.NORTH,label1);

		return button;

	}
	
	/**
	 * Method to create a button for the events
	 * 
	 * @param son panel to apply the scroll bar
	 * @return JScrollPane created
	 */
	public static JScrollPane createScrollBar(JPanel son) {
	    JScrollPane scrollPane = new JScrollPane(son);
	    scrollPane.setPreferredSize(new Dimension(1500, 700));
	    return scrollPane;
	    
	}
	
	/**
	 * Method to add a listener for the event button
	 * 
	 * @param button to add a listener for the event button
	 * @param event of the button
	 * @param parent main frame
	 * @param app containing all the info of the app
	 */
	public static void addListener(JButton button, Event event, MainFrame parent, TheaterApp app) {
		button.addActionListener(e->{
			button.setBackground(Color.BLUE);
			
			if(event instanceof TheaterPlay)
	       		parent.changeView(new TheaterPlayInterface(event, parent, app));
			if(event instanceof Concert)
	       		parent.changeView(new ConcertInterface(event, parent, app));
			if(event instanceof Dance)
				parent.changeView(new DanceInterface(event, parent, app));
			if(event instanceof Cycle)
				parent.changeView(new CycleInterface(event, parent, app));
		});
	}

	/**
	 * Method to add a listener for the pass button
	 * 
	 * @param button to add a listener for the event button
	 * @param pass of the button
	 * @param parent main frame
	 * @param app containing all the info of the app
	 */
	public static void addListener(JButton button, Pass pass, MainFrame parent, TheaterApp app) {
		button.addActionListener(e->{
		parent.changeView(new PassInterface(pass, parent, app));
	});
	}

	/**
	 * Method to add a listener for the back button
	 * 
	 * @param button to add a listener for the back button
	 * @param parent main frame
	 * @param app containing all the info of the app
	 */
	public static void addListener(JButton button, MainFrame parent, TheaterApp app) {
		button.addActionListener(e->{
		parent.changeView(new PassInterface(parent, app));
	});
	}

}
