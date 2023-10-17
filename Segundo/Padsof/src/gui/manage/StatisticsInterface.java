package gui.manage;


import app.TheaterApp;
import events.Cycle;
import events.Event;
import events.Price;
import gui.mainform.MainFrame;
import gui.topBar.AdminInterface;
import performances.Performance;
import performances.Ticket;
import users.Customer;
import zones.*;

import java.awt.*;
import java.time.LocalDateTime;
import java.util.ArrayList;

import javax.swing.*;
/**
 * This is a class that allow us to create the statistics interface
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class StatisticsInterface extends JPanel{
	private Event event;
	private Performance performance;
	private JComboBox<String> eBox;
	private JComboBox<LocalDateTime> pBox;

	/**
	 * Method to create the statistics interface
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 */
	public StatisticsInterface(MainFrame parent, TheaterApp app)	{
		
		
		
		this.setLayout(new BorderLayout());
		this.add(new AdminInterface(parent,app),BorderLayout.NORTH);
		

		JPanel tab1= new JPanel();
		JPanel tab2= new JPanel();
		JPanel tab3= new JPanel();

		JTabbedPane tabs= new JTabbedPane();
		tabs.setBounds(100, 80, 100, 80);
		this.add(tabs,BorderLayout.CENTER);
		// Add panels to container using the method addTab(<title>,<panel>)
		tabs.addTab("Event", tab1);
		tabs.addTab("Performance", tab2);
		tabs.addTab("Zone", tab3);
		
		JPanel  eventTable = stat_Event(app);
		tab1.add(eventTable);
		JPanel  performanceTable = stat_Performance(app);
		tab2.add(performanceTable);
		JPanel  zoneTable = stat_Zone(app);
		tab3.add(zoneTable);
	}
	
	/**
	 * Method to create the statistics of an event
	 * 
	 * @param app containing all the info of the app
	 * @return JPanel created
	 */
	public JPanel stat_Event(TheaterApp app){

		String[] titles= {"Event", "Occupancy","Profits"};
		ArrayList<Object[]>  list = new ArrayList<>();
		for(Event e : app.getEvents())	{
			if (!(e instanceof Cycle))	{
				app.updateEventStatistic(e.getTitle());
				Object[] o = { e.getTitle(), app.getEventStatistic(e.getTitle()).getOccupancy(), app.getEventStatistic(e.getTitle()).getProfits()	};
				list.add(o);
			}
		}
		Object[][] rows= new Object[list.size()][3];
		rows = list.toArray(rows);
		

		JTable table = new JTable(rows, titles);

		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		table.setPreferredScrollableViewportSize(new Dimension(1500, 150));

		//table.setPreferredScrollableViewportSize(new Dimension(500, 80));
		JScrollPane scrollBar= new JScrollPane(table);
		JPanel tablePanel= new JPanel();
		tablePanel.add(scrollBar);
		return tablePanel;
	}
	
	/**
	 * Method to create the statistics of a performance
	 * 
	 * @param app containing all the info of the app
	 * @return JPanel created
	 */
	public JPanel stat_Performance(TheaterApp app){

		ArrayList<String> eventNames = new ArrayList<>();
		JPanel combo = new JPanel();
		combo.setLayout(new BorderLayout());
		JPanel tablePanel= new JPanel();
		
		
		
		// Events
		String[] titles= {"Performance", "Occupancy","Profits"};
		ArrayList<Object[]>  list = new ArrayList<>();
		for(Event e : app.getEvents())	{
			if (!(e instanceof Cycle))	{
				eventNames.add(e.getTitle());
			}
		}
		String[] str= new String[eventNames.size()];
		str = eventNames.toArray(str);
		JComboBox<String> eventBox = new JComboBox<String>(str);
		eventBox.setSelectedIndex(0);
		this.event = app.getEvent((String)eventBox.getSelectedItem());
		/*****************************************************/
		/*****************************************************/
		
		eventBox.addActionListener(e -> {

			this.event = app.getEvent((String)eventBox.getSelectedItem());
			ArrayList<Object[]>  list2 = new ArrayList<>();
			

			// Performances
			for(Performance p : this.event.getPerformances())	{
				app.updatePerformanceStatistic(this.event.getTitle(), p.getDate());
				Object[] o = { p.getDate(), app.getPerformanceStatistic(this.event.getTitle(),p.getDate()).getOccupancy(), app.getPerformanceStatistic(this.event.getTitle(),p.getDate()).getProfits()	};
				list2.add(o);
			}
			if(list2.isEmpty()) {
				return;
			}
			


			this.repaint();
			this.revalidate();
			
			Object[][] rows= new Object[list2.size()][3];
			rows = list2.toArray(rows);
			
			
			
			JTable table2 = new JTable(rows, titles);


			table2.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
			table2.setPreferredScrollableViewportSize(new Dimension(1500, 150));
			JScrollPane scrollBar2= new JScrollPane(table2);
			
			tablePanel.removeAll();
			tablePanel.add(scrollBar2);
			tablePanel.repaint();

			
		});
		
		/*****************************************************/
		/*****************************************************/
		// Performances
		
		for(Performance p : this.event.getPerformances())	{
			app.updatePerformanceStatistic(this.event.getTitle(), p.getDate());
			Object[] o = { p.getDate(), app.getPerformanceStatistic(this.event.getTitle(),p.getDate()).getOccupancy(), app.getPerformanceStatistic(this.event.getTitle(),p.getDate()).getProfits()	};
			list.add(o);
		}
		
		Object[][] rows= new Object[list.size()][3];
		rows = list.toArray(rows);
		

		JTable table = new JTable(rows, titles);

		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

		table.setPreferredScrollableViewportSize(new Dimension(1500, 150));
		
		JScrollPane scrollBar= new JScrollPane(table);
		
		tablePanel.add(scrollBar);
		
		combo.add(eventBox,BorderLayout.NORTH);
		combo.add(tablePanel,BorderLayout.CENTER);

		return combo;
	}
	
	/**
	 * Method to create the statistics of a zone
	 * 
	 * @param app containing all the info of the app
	 * @return JPanel created
	 */
	public JPanel stat_Zone(TheaterApp app){
		JPanel types = new JPanel();
		JPanel tab1= new JPanel();
		JPanel tab2= new JPanel();
		JPanel tab3= new JPanel();

		JTabbedPane tabs= new JTabbedPane();
		tabs.setBounds(100, 80, 100, 80);
		types.add(tabs);
		// Add panels to container using the method addTab(<title>,<panel>)
		tabs.addTab("All Events", tab1);
		tabs.addTab("Filter by event", tab2);
		tabs.addTab("Filter by performance", tab3);
		JPanel  zone1Table = stat_Zone_All(app);
		tab1.add(zone1Table);
		
		JPanel  zone2Table = stat_Zone_Event(app);
		tab2.add(zone2Table);
		
		JPanel  zone3Table = stat_Zone_Performance(app);
		tab3.add(zone3Table);
		
		return types;
		
	}
	
	/**
	 * Method to create the statistics of all zones
	 * 
	 * @param app containing all the info of the app
	 * @return JPanel created
	 */
	public JPanel stat_Zone_All(TheaterApp app){
		
		String[] titles= {"Zone", "Occupancy","Profits"};
		ArrayList<Object[]>  list = new ArrayList<>();
		for(Zone z : app.getAllZones())	{
				app.updateZoneStatistic(z.getName());
				Object[] o = { z.getName(), app.getZoneStatistic(z.getName()).getOccupancy(), app.getZoneStatistic(z.getName()).getProfits()	};
				list.add(o);
			
		}
		Object[][] rows= new Object[list.size()][3];
		rows = list.toArray(rows);
		

		JTable table = new JTable(rows, titles);

		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		table.setPreferredScrollableViewportSize(new Dimension(1500, 80));

		//table.setPreferredScrollableViewportSize(new Dimension(500, 80));
		JScrollPane scrollBar= new JScrollPane(table);
		JPanel tablePanel= new JPanel();
		tablePanel.add(scrollBar);
		return tablePanel;
	}
	
	/**
	 * Method to create the statistics of a zone depending on an event
	 * 
	 * @param app containing all the info of the app
	 * @return JPanel created
	 */
	public JPanel stat_Zone_Event(TheaterApp app){

		ArrayList<String> eventNames = new ArrayList<>();
		JPanel combo = new JPanel();
		combo.setLayout(new BorderLayout());
		JPanel tablePanel= new JPanel();
		
		
		
		// Events
		String[] titles= {"Zone", "Occupancy","Profits"};
		ArrayList<Object[]>  list = new ArrayList<>();
		for(Event e : app.getEvents())	{
			if (!(e instanceof Cycle))	{
				eventNames.add(e.getTitle());
			}
		}
		String[] str= new String[eventNames.size()];
		str = eventNames.toArray(str);
		JComboBox<String> eventBox = new JComboBox<String>(str);
		eventBox.setSelectedIndex(0);
		this.event = app.getEvent((String)eventBox.getSelectedItem());
		/*****************************************************/
		/*****************************************************/
		
		eventBox.addActionListener(e -> {

			this.event = app.getEvent((String)eventBox.getSelectedItem());
			ArrayList<Object[]>  list2 = new ArrayList<>();
			

			// Zones
			for(Zone z : app.getAllZones())	{
				app.updateEventZoneStatistic(this.event.getTitle(), z.getName());
				Object[] o = { z.getName(), app.getZoneStatistic(z.getName()).getOccupancy(), app.getZoneStatistic(z.getName()).getProfits()	};
				list2.add(o);
			}
			if(list2.isEmpty()) {
				return;
			}
			


			this.repaint();
			this.revalidate();
			
			Object[][] rows= new Object[list2.size()][3];
			rows = list2.toArray(rows);
			
			
			
			JTable table2 = new JTable(rows, titles);


			table2.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
			table2.setPreferredScrollableViewportSize(new Dimension(1500, 150));
			JScrollPane scrollBar2= new JScrollPane(table2);
			
			tablePanel.removeAll();
			tablePanel.add(scrollBar2);
			tablePanel.repaint();

			
		});
		
		/*****************************************************/
		/*****************************************************/
		// Zones
		for(Zone z : app.getAllZones())	{
			app.updateEventZoneStatistic(this.event.getTitle(), z.getName());
			Object[] o = { z.getName(), app.getZoneStatistic(z.getName()).getOccupancy(), app.getZoneStatistic(z.getName()).getProfits()	};
			list.add(o);
		}
		
		Object[][] rows= new Object[list.size()][3];
		rows = list.toArray(rows);
		

		JTable table = new JTable(rows, titles);

		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

		table.setPreferredScrollableViewportSize(new Dimension(1500, 150));
		
		JScrollPane scrollBar= new JScrollPane(table);
		
		tablePanel.add(scrollBar);
		
		combo.add(eventBox,BorderLayout.NORTH);
		combo.add(tablePanel,BorderLayout.CENTER);

		return combo;
	}
	
	/**
	 * Method to create the statistics of a zone depending on a performance
	 * 
	 * @param app containing all the info of the app
	 * @return JPanel created
	 */
	public JPanel stat_Zone_Performance(TheaterApp app){

		ArrayList<String> eventNames = new ArrayList<>();
		JPanel combo = new JPanel();
		combo.setLayout(new BorderLayout());
		JPanel tablePanel= new JPanel();
		JPanel subCombo = new JPanel();
		
		
		// Events
		String[] titles= {"Zone", "Occupancy","Profits"};
		ArrayList<Object[]>  list = new ArrayList<>();
		for(Event e : app.getEvents())	{
			if (!(e instanceof Cycle))	{
				eventNames.add(e.getTitle());
			}
		}
		// Inicializamos caja de eventos
		String[] str= new String[eventNames.size()];
		str = eventNames.toArray(str);
		this.eBox = new JComboBox<String>(str);
		eBox.setSelectedIndex(0);
		this.event = app.getEvent((String)eBox.getSelectedItem());
		
		// Performances
		ArrayList<LocalDateTime> performanceDates = new ArrayList<>();
		for(Performance p : this.event.getPerformances())	{
			performanceDates.add(p.getDate());
		}
		// Inicializamos caja de performances
		LocalDateTime[] str2 = new LocalDateTime[performanceDates.size()];
		str2 = performanceDates.toArray(str2);
		this.pBox = new JComboBox<LocalDateTime>(str2);
		pBox.setSelectedIndex(0);
		this.performance = app.getPerformance(this.event.getTitle(),(LocalDateTime)pBox.getSelectedItem());
		/*****************************************************/
		/*****************************************************/
		
		eBox.addActionListener(e -> {
			this.event = app.getEvent((String)eBox.getSelectedItem());
			// Rehacemos performances
			ArrayList<LocalDateTime> performanceDates2 = new ArrayList<>();
			for(Performance p : this.event.getPerformances())	{
				performanceDates2.add(p.getDate());
			}
			// Rehacemos caja de performances
			LocalDateTime[] str3 = new LocalDateTime[performanceDates2.size()];
			str3 = performanceDates2.toArray(str3);
			pBox = new JComboBox<LocalDateTime>(str3);
			pBox.setSelectedItem(performanceDates2.get(0));
			this.performance = app.getPerformance(this.event.getTitle(),(LocalDateTime)pBox.getSelectedItem());
			

			/*****************************************************/
			/*****************************************************/
			
			pBox.addActionListener(e2 -> {

				this.performance = app.getPerformance(this.event.getTitle(),(LocalDateTime)pBox.getSelectedItem());
				ArrayList<Object[]>  list2 = new ArrayList<>();
				

				// Zones
				for(Zone z : app.getAllZones())	{
					app.updatePerformanceZoneStatistic(this.event.getTitle(),this.performance.getDate() ,z.getName());
					Object[] o = { z.getName(), app.getZoneStatistic(z.getName()).getOccupancy(), app.getZoneStatistic(z.getName()).getProfits()	};
					list2.add(o);
				}
				if(list2.isEmpty()) {
					return;
				}
				


				this.repaint();
				this.revalidate();
				
				Object[][] rows= new Object[list2.size()][3];
				rows = list2.toArray(rows);
				
				
				
				JTable table2 = new JTable(rows, titles);


				table2.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
				table2.setPreferredScrollableViewportSize(new Dimension(1500, 150));
				JScrollPane scrollBar2= new JScrollPane(table2);
				
				tablePanel.removeAll();
				tablePanel.add(scrollBar2);
				tablePanel.repaint();

				
			});
			
			// Zones
			
			for(Zone z : app.getAllZones())	{
				app.updatePerformanceZoneStatistic(this.event.getTitle(), this.performance.getDate(), z.getName());
				Object[] o = { z.getName(), app.getZoneStatistic(z.getName()).getOccupancy(), app.getZoneStatistic(z.getName()).getProfits()	};
				list.add(o);
			}
			
			Object[][] rows= new Object[list.size()][3];
			rows = list.toArray(rows);
			

			JTable table = new JTable(rows, titles);

			table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

			table.setPreferredScrollableViewportSize(new Dimension(1500, 150));
			
			JScrollPane scrollBar= new JScrollPane(table);
			tablePanel.removeAll();
			tablePanel.add(scrollBar);
			subCombo.removeAll();
			subCombo.add(eBox);
			subCombo.add(pBox);
			combo.add(tablePanel,BorderLayout.CENTER);


			
		});
		
		/*****************************************************/
		for(Zone z : app.getAllZones())	{
			app.updateEventZoneStatistic(this.event.getTitle(), z.getName());
			Object[] o = { z.getName(), app.getZoneStatistic(z.getName()).getOccupancy(), app.getZoneStatistic(z.getName()).getProfits()	};
			list.add(o);
		}
		
		Object[][] rows= new Object[list.size()][3];
		rows = list.toArray(rows);
		

		JTable table = new JTable(rows, titles);

		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

		table.setPreferredScrollableViewportSize(new Dimension(1500, 150));
		
		JScrollPane scrollBar= new JScrollPane(table);
		
		tablePanel.add(scrollBar);
		

		subCombo.add(eBox);
		subCombo.add(pBox);
		combo.add(subCombo,BorderLayout.NORTH);
		combo.add(tablePanel,BorderLayout.CENTER);

		return combo;
	}
}
