package gui.manage;

import java.awt.BorderLayout;

import javax.persistence.Column;
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
import gui.mainform.MainPanel;
import zones.FragmentedZone;
import zones.Seat;
import zones.SittingZone;
import zones.StandingZone;
import zones.Zone;
/**
 * This is a class that allow us to create the manage theater interface
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class ManageTheaterInterface extends JPanel {

	/**
	 * Method to create the manage theater interface
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 */
	public ManageTheaterInterface(MainFrame parent, TheaterApp app) {
		this.setPreferredSize(new Dimension(1500, 800));
		this.setLayout(new GridLayout(0, 2));

		JTabbedPane tabs1 = new JTabbedPane();
		tabs1.addTab("Create Zone", createZone(parent, app));
		tabs1.addTab("Delete Zone", deleteZone(parent, app));
		tabs1.setBounds(50, 50, 50, 50);
		this.add(tabs1);
		JTabbedPane tabs2 = new JTabbedPane();
		tabs2.addTab("Maintain", manageSeats(parent, app));
		tabs2.addTab("Occupancy", occupancy(parent, app));
		tabs2.addTab("TTB/TTP", timeTo(parent, app));
		tabs2.setBounds(50, 50, 50, 50);
		this.add(tabs2);
		
	}

	/**
	 * Method to create the panel to delete a zone
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 * @return JPanel with the created panel
	 */
	public JPanel deleteZone(MainFrame parent, TheaterApp app) {
		JPanel delete = new JPanel();
		delete.setLayout(new GridLayout(0, 1));
		JLabel zones = new JLabel("Zones : ");
		JComboBox<String> deleteZones = new JComboBox<String>();
		
		for (Zone zone : app.getZones()) {
			if (zone instanceof FragmentedZone) {
				deleteZones.addItem(zone.getName());
				for (Zone sz : ((FragmentedZone) zone).getUsableSubZones()) {
					deleteZones.addItem(sz.getName());
				}
			} else {
				deleteZones.addItem(zone.getName());
			}
		}

		delete.add(deleteZones);
		delete.add(zones);

		JButton deleteZ = new JButton("Delete Zone");
		JButton deleteAll = new JButton("Delete All");

		deleteZ.addActionListener(e -> {
			app.deleteZone(app.getZone(deleteZones.getSelectedItem().toString()));
			JOptionPane.showMessageDialog(deleteZ, "Zone Deleted");
			parent.changeView(new MainPanel(parent, app));
		});

		deleteAll.addActionListener(e -> {
			for(Zone z: app.getZones()) {
				app.deleteZone(z);
			}
			JOptionPane.showMessageDialog(deleteAll, "All Zones Deleted");
			parent.changeView(new MainPanel(parent, app));
		});


		delete.add(deleteZ);
		delete.add(deleteAll);
		return delete;
	}

	/**
	 * Method to create the panel to create a zone
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 * @return JPanel with the created panel
	 */
	public JPanel createZone(MainFrame parent, TheaterApp app) {
		JPanel create = new JPanel();
		create.setLayout(new GridLayout(0, 1));
		
		JTabbedPane tabs = new JTabbedPane();
		tabs.addTab("Zone", createZ(parent, app));
		tabs.addTab("Subzone", createSubZ(parent, app));
		tabs.setBounds(50, 50, 50, 50);
		create.add(tabs);
		
		return create;
	}
	
	/**
	 * Method to create the subpanel to create a zone
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 * @return JPanel with the created panel
	 */
	public JPanel createZ(MainFrame parent, TheaterApp app) {
		JPanel createZ = new JPanel();
		createZ.setLayout(new GridLayout(0, 1));
		JLabel type = new JLabel("Zone type : ");
		JComboBox<String> option = new JComboBox<String>();
		option.addItem("Standing");
		option.addItem("Sitting");
		option.addItem("Composed");
		JLabel zones = new JLabel("Zone name : ");
		JTextField zoneName = new JTextField();
		JLabel passPrice = new JLabel("Annual Pass price : ");
		JTextField price = new JTextField();
		JLabel people = new JLabel("Max People : ");
		JTextField npeople = new JTextField();
		JLabel rows = new JLabel("Number rows : ");
		JTextField nrows = new JTextField();
		JLabel columns = new JLabel("Number columns : ");
		JTextField ncols = new JTextField();
		
		createZ.add(type);
		createZ.add(option);
		createZ.add(passPrice);
		createZ.add(price);
		createZ.add(zones);
		createZ.add(zoneName);
		createZ.add(people);
		createZ.add(npeople);
		createZ.add(rows);
		createZ.add(nrows);
		createZ.add(columns);
		createZ.add(ncols);

		JButton create = new JButton("Create Zone");

		npeople.addKeyListener(new KeyAdapter(){
			public void keyTyped(KeyEvent e) {
        	char c = e.getKeyChar();
        	if (!(Character.isDigit(c) || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))) {
                getToolkit().beep();
				e.consume();
				JOptionPane.showMessageDialog(createZ, "Insert only numbers");
            }
         }
		});

		nrows.addKeyListener(new KeyAdapter(){
			public void keyTyped(KeyEvent e) {
        	char c = e.getKeyChar();
        	if (!(Character.isDigit(c) || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))) {
                getToolkit().beep();
				e.consume();
				JOptionPane.showMessageDialog(createZ, "Insert only numbers");
            }
         }
		});

		ncols.addKeyListener(new KeyAdapter(){
			public void keyTyped(KeyEvent e) {
        	char c = e.getKeyChar();
        	if (!(Character.isDigit(c) || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))) {
                getToolkit().beep();
				e.consume();
				JOptionPane.showMessageDialog(createZ, "Insert only numbers");
            }
         }
		});

		create.addActionListener(e -> {
			if(option.getSelectedItem().toString().equals("Standing")) {
				app.createStandingZone(zoneName.getText(), Integer.parseInt(npeople.getText()), Double.parseDouble(price.getText()));
			}else if(option.getSelectedItem().toString().equals("Standing")) {
				app.createSittingZone(zoneName.getText(), Integer.parseInt(nrows.getText()), Integer.parseInt(ncols.getText()), Double.parseDouble(price.getText()));
			}else if(option.getSelectedItem().toString().equals("Composed")) {
				app.createFragmentedZone(zoneName.getText());
			}
			JOptionPane.showMessageDialog(create, "Zone Created");
			parent.changeView(new MainPanel(parent, app));
			});

		createZ.add(create);

		return createZ;
	}
	
	/**
	 * Method to create the subpanel to create a subzone
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 * @return JPanel with the created panel
	 */
	public JPanel createSubZ(MainFrame parent, TheaterApp app) {
		JPanel createZ = new JPanel();
		createZ.setLayout(new GridLayout(0, 1));
		JLabel pZoneName = new JLabel("Parent zone : ");
		JComboBox<String> parentZone = new JComboBox<String>();
		
		for(Zone z :app.getFragmentedZones()) {
			parentZone.addItem(z.getName());
		}
		
		JLabel type = new JLabel("Zone type : ");
		JComboBox<String> option = new JComboBox<String>();
		option.addItem("Standing");
		option.addItem("Sitting");
		option.addItem("Composed");
		JLabel zones = new JLabel("Zone name : ");
		JTextField zoneName = new JTextField();
		JLabel passPrice = new JLabel("Annual Pass price : ");
		JTextField price = new JTextField();
		JLabel people = new JLabel("Max People : ");
		JTextField npeople = new JTextField();
		JLabel rows = new JLabel("Number rows : ");
		JTextField nrows = new JTextField();
		JLabel columns = new JLabel("Number columns : ");
		JTextField ncols = new JTextField();
		
		createZ.add(pZoneName);
		createZ.add(parentZone);
		createZ.add(type);
		createZ.add(option);
		createZ.add(passPrice);
		createZ.add(price);
		createZ.add(zones);
		createZ.add(zoneName);
		createZ.add(people);
		createZ.add(npeople);
		createZ.add(rows);
		createZ.add(nrows);
		createZ.add(columns);
		createZ.add(ncols);

		JButton create = new JButton("Create Zone");

		npeople.addKeyListener(new KeyAdapter(){
			public void keyTyped(KeyEvent e) {
        	char c = e.getKeyChar();
        	if (!(Character.isDigit(c) || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))) {
                getToolkit().beep();
				e.consume();
				JOptionPane.showMessageDialog(create, "Insert only numbers");
            }
         }
		});

		ncols.addKeyListener(new KeyAdapter(){
			public void keyTyped(KeyEvent e) {
        	char c = e.getKeyChar();
        	if (!(Character.isDigit(c) || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))) {
                getToolkit().beep();
				e.consume();
				JOptionPane.showMessageDialog(create, "Insert only numbers");
            }
         }
		});

		nrows.addKeyListener(new KeyAdapter(){
			public void keyTyped(KeyEvent e) {
        	char c = e.getKeyChar();
        	if (!(Character.isDigit(c) || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))) {
                getToolkit().beep();
				e.consume();
				JOptionPane.showMessageDialog(create, "Insert only numbers");
            }
         }
		});

		create.addActionListener(e -> {
			if(option.getSelectedItem().toString().equals("Standing")) {
				app.createStandingZone(zoneName.getText(), Integer.parseInt(npeople.getText()),parentZone.getSelectedItem().toString(), Double.parseDouble(price.getText()));
			}else if(option.getSelectedItem().toString().equals("Standing")) {
				app.createSittingZone(zoneName.getText(), Integer.parseInt(nrows.getText()), Integer.parseInt(ncols.getText()),parentZone.getSelectedItem().toString(),Double.parseDouble(price.getText()));
			}else if(option.getSelectedItem().toString().equals("Composed")) {
				app.createFragmentedZone(zoneName.getText(),parentZone.getSelectedItem().toString());
			}
			JOptionPane.showMessageDialog(create, "Zone Created");
			parent.changeView(new MainPanel(parent, app));
			});

		createZ.add(create);

		return createZ;
	}

	/**
	 * Method to create the panel to manage the seats
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 * @return JPanel with the created panel
	 */
	public JPanel manageSeats(MainFrame parent, TheaterApp app){
		JPanel manage = new JPanel();
		manage.setLayout(new GridLayout(0, 1));

		JLabel zoneName = new JLabel("Zone Name :");
		JComboBox<String> zones = new JComboBox<String>();
		for(Zone z : app.getUsableZones()){
			if(z instanceof SittingZone){
				zones.addItem(z.getName());
			}
		}
		JLabel labelRow = new JLabel("Row: ");
		JTextField rows = new JTextField();
		JLabel labelCol = new JLabel("Column: ");
		JTextField columns = new JTextField();
		JLabel dateInfo = new JLabel("End Date (dd/mm/yyyy): ");
		JTextField date = new JTextField();
		JLabel mInfo = new JLabel("Reason: ");
		JTextField reason = new JTextField();
		JButton editSeat = new JButton("Submit");

		manage.add(zoneName);
		manage.add(zones);
		manage.add(labelRow);
		manage.add(rows);
		manage.add(labelCol);
		manage.add(columns);
		manage.add(dateInfo);
		manage.add(date);
		manage.add(mInfo);
		manage.add(reason);
		manage.add(editSeat);

		rows.addKeyListener(new KeyAdapter(){
			public void keyTyped(KeyEvent e) {
        	char c = e.getKeyChar();
        	if (!(Character.isDigit(c) || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))) {
                getToolkit().beep();
				e.consume();
				JOptionPane.showMessageDialog(manage, "Insert only numbers");
            }
         }
		});

		columns.addKeyListener(new KeyAdapter(){
			public void keyTyped(KeyEvent e) {
        	char c = e.getKeyChar();
        	if (!(Character.isDigit(c) || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))) {
                getToolkit().beep();
				e.consume();
				JOptionPane.showMessageDialog(manage, "Insert only numbers");
            }
         }
		});		

		editSeat.addActionListener(e->{
			DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");
			LocalDate dateTime = LocalDate.parse(date.getText(), formatter);
			if(app.mantainSeat(zones.getSelectedItem().toString(), Integer.parseInt(rows.getText()), Integer.parseInt(columns.getText()), dateTime, reason.getText())==false){
				JOptionPane.showMessageDialog(manage, "Something is wrong. Try again");
			}else{
			JOptionPane.showMessageDialog(manage, "Maintenance has started");
			}
		});

		return manage;
	}

	/**
	 * Method to create the panel to set the occupancy
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 * @return JPanel with the created panel
	 */
	public JPanel occupancy(MainFrame parent, TheaterApp app){
		JPanel occupancy = new JPanel();
		occupancy.setLayout(new GridLayout(0, 1));

		JLabel zoneName = new JLabel("Zone Occupancy Percentage :");
		JComboBox<String> zones = new JComboBox<String>();
		for(Zone z : app.getAllZones()){
			zones.addItem(z.getName());
		}
		JTextField percentage1 = new JTextField();
		JButton occZone = new JButton("Apply");

		JLabel theater  = new JLabel("Theater Occupancy Percentage :");
		JTextField percentage2 = new JTextField();
		JButton occAll = new JButton("Apply");

		occupancy.add(zoneName);
		occupancy.add(zones);
		occupancy.add(percentage1);
		occupancy.add(occZone);
		occupancy.add(theater);
		occupancy.add(percentage2);
		occupancy.add(occAll);

		percentage1.addKeyListener(new KeyAdapter(){
			public void keyTyped(KeyEvent e) {
        	char c = e.getKeyChar();
        	if (!(Character.isDigit(c) || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))) {
                getToolkit().beep();
				e.consume();
				JOptionPane.showMessageDialog(occupancy, "Insert only numbers");
            }
         }
		});

		percentage2.addKeyListener(new KeyAdapter(){
			public void keyTyped(KeyEvent e) {
        	char c = e.getKeyChar();
        	if (!(Character.isDigit(c) || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))) {
                getToolkit().beep();
				e.consume();
				JOptionPane.showMessageDialog(occupancy, "Insert only numbers");
            }
         }
		});

		occZone.addActionListener(e->{
			app.getZone(zones.getSelectedItem().toString()).setOccupancy(Integer.parseInt(percentage1.getText()));
			JOptionPane.showMessageDialog(occupancy, "The zone occupancy has changed");
		});

		occAll.addActionListener(e->{
			app.setOccupancy(Integer.parseInt(percentage1.getText()));
			JOptionPane.showMessageDialog(occupancy, "The theater occupancy has changed");
		});

		return occupancy;
	}


<<<<<<< HEAD:src/gui/manage/ManageTheaterInterface.java
	/**
	 * Method to create the panel to set the ttb and the ttp
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 * @return JPanel with the created panel
	 */
=======
>>>>>>> 1cd9b5ca3eae2f21b66106514195f08a9f18320b:src/gui/mainform/ManageTheaterInterface.java
	public JPanel timeTo(MainFrame parent, TheaterApp app){
		JPanel time = new JPanel();
		time.setLayout(new GridLayout(0, 1));
		JLabel ttb = new JLabel("TTB(Time To Book) hours :");
		JTextField newttb = new JTextField();
		JButton ttbbutton = new JButton("OK");
		JLabel ttp = new JLabel("TTP(Time To Pay) hours :");
		JTextField newttp = new JTextField();
		JButton ttpbutton = new JButton("OK");

		time.add(ttb);
		time.add(newttb);
		time.add(ttbbutton);
		time.add(ttp);
		time.add(newttp);
		time.add(ttpbutton);

		newttb.addKeyListener(new KeyAdapter(){
			public void keyTyped(KeyEvent e) {
        	char c = e.getKeyChar();
        	if (!(Character.isDigit(c) || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))) {
                getToolkit().beep();
				e.consume();
				JOptionPane.showMessageDialog(time, "Insert only numbers");
            }
         }
		});

		newttp.addKeyListener(new KeyAdapter(){
			public void keyTyped(KeyEvent e) {
        	char c = e.getKeyChar();
        	if (!(Character.isDigit(c) || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))) {
                getToolkit().beep();
				e.consume();
				JOptionPane.showMessageDialog(time, "Insert only numbers");
            }
         }
		});

		ttbbutton.addActionListener(e -> {
			app.setTTB(Integer.parseInt(newttb.getText()));
			JOptionPane.showMessageDialog(ttbbutton, "New TTB established");
			});

		ttpbutton.addActionListener(e -> {
			app.setTTP(Integer.parseInt(newttp.getText()));
			JOptionPane.showMessageDialog(ttpbutton, "New TTP established");
			});


		return time;
	}

}