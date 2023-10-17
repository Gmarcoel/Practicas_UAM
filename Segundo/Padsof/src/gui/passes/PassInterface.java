package gui.passes;

import app.TheaterApp;
import events.Cycle;
import events.Event;
import events.Price;
import gui.mainform.MainFrame;
import gui.mainform.MainPanel;
import gui.topBar.AdminInterface;
import gui.topBar.LoginRegisterInterface;
import gui.topBar.UserInterface;
import gui.payments.PayPanel;
import events.Pass;
import events.CyclePass;
import events.AnnualPass;
import performances.Performance;
import zones.Zone;
import users.Customer;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.awt.*;
import java.util.ArrayList;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
/**
 * This is a class that allow us to create the pass interface
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class PassInterface extends JPanel {
	private double price =0;
	private Zone zone = null;
<<<<<<< HEAD:src/gui/passes/PassInterface.java

	/**
	 * Method to create the pass interface
	 * 
	 * @param pass pass to create the interface of
	 * @param parent main frame
	 * @param app containing all the info of the app
	 */
=======
>>>>>>> 1cd9b5ca3eae2f21b66106514195f08a9f18320b:src/gui/mainform/PassInterface.java
	public PassInterface(Pass pass, MainFrame parent, TheaterApp app) {
		this.setLayout(new BorderLayout());
		if(parent.getLoged()==false) {
			this.add(new LoginRegisterInterface(parent, app), BorderLayout.NORTH);
			
		}
		else if (!(parent.getCurrentUser().equals("admin"))) {
			this.add(new UserInterface(parent, app), BorderLayout.NORTH);
		}

		else {		
			this.add(new AdminInterface(parent, app));
			JPanel panel = adminMode(pass, parent, app); 
			this.add(panel, BorderLayout.CENTER);
			return;
		}
		
		JPanel container = setText(pass);

		JButton button = new JButton("Back");
		button.setPreferredSize(new Dimension(80, 60));
		addListener(button, parent, app);

		JPanel subContainer = new JPanel();
		subContainer.setLayout(new BorderLayout());
		subContainer.add(button, BorderLayout.EAST);

		if(parent.getLoged()==true) {
				
				JButton b2 = new JButton("Buy");
				b2.setFont(b2.getFont().deriveFont(56.0f));
				b2.addActionListener(e->{
					
					parent.changeView(new PayPanel(parent, app, pass));
				});
				subContainer.add(b2, BorderLayout.CENTER);
		}
			container.add(subContainer, BorderLayout.SOUTH);
		

		this.add(container, BorderLayout.CENTER);

	}
	
<<<<<<< HEAD:src/gui/passes/PassInterface.java
	/**
	 * Method to create the pass interface
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 */
=======
	
	
	
	
	
>>>>>>> 1cd9b5ca3eae2f21b66106514195f08a9f18320b:src/gui/mainform/PassInterface.java
	public PassInterface(MainFrame parent, TheaterApp app) {

		JPanel container = setText(parent, app);

		JButton button = new JButton("Back");
		button.setPreferredSize(new Dimension(80, 60));
		addListener(button, parent, app);
		JPanel subContainer = new JPanel();
		subContainer.setLayout(new BorderLayout());
		subContainer.add(button, BorderLayout.EAST);
		if(parent.getLoged()==true) {
			if(!(parent.getCurrentUser().equals("admin"))){
			if(((Customer)app.getCustomer(parent.getCurrentUser())).getAnnualPass()==null) {
				JButton b2 = new JButton("Buy");
				b2.setFont(b2.getFont().deriveFont(56.0f));
				b2.addActionListener(e->{
					
					parent.changeView(new PayPanel(parent, app, new AnnualPass(this.price, this.zone)));
				});
				subContainer.add(b2, BorderLayout.CENTER);
			}
			}
		}
			container.add(subContainer, BorderLayout.SOUTH);
		

		this.add(container);

	}
	
	
	/**
	 * Method to set the text of the panel
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 * @return JPanel created
	 */
	public JPanel setText(MainFrame parent, TheaterApp app) {
		JPanel container = new JPanel();
		container.setLayout(new GridLayout(0, 1));

		JLabel label1 = new JLabel("Annual Pass");
		label1.setFont(label1.getFont().deriveFont(128.0f));
		container.add(label1);

		JComboBox<String> zones = new JComboBox<String>();
		for(Zone z : app.getUsableZones()) {
			zones.addItem(z.getName());
		}

		LocalDateTime now= LocalDateTime.now();
		now.plusYears(1);

		DateTimeFormatter dtf = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm:ss");  
		JLabel label2 = new JLabel("You have access to all the plays until "+dtf.format(now));
		label1.setFont(label1.getFont().deriveFont(128.0f));
		container.add(label2);
		container.add(zones);
		
		
		
		if(parent.getLoged()==true && parent.getCurrentUser().equals("admin")) {
			JLabel priceLabel = new JLabel("Price :");
			container.add(priceLabel);
			JTextField price = new JTextField(5);
			JButton save = new JButton("SAVE PRICE");
			zones.addActionListener(e->{
				this.zone=app.getZone((String)zones.getSelectedItem());
				this.price=app.getAnnualPassPrice(this.zone);
				price.setText(Double.toString((this.price)));
				
			});
			save.addActionListener(e->{
				this.price=Double.parseDouble(price.getText());
				app.setAnnualPassPrice(this.price, this.zone);
				JOptionPane.showMessageDialog(save, "Annual pass price for zone "+this.zone.getName()+" modified");
				parent.changeView(new MainPanel(parent, app));
				
			});
			container.add(price);
			container.add(save);
			
		}
		else {
		JLabel price = new JLabel("Price : Select Zone");
		
		zones.addActionListener(e->{
			this.zone=app.getZone((String)zones.getSelectedItem());
			this.price=app.getAnnualPassPrice(this.zone);
			price.setText("Price : "+this.price);
			
		});
		container.add(price);
		}
		

		
		container.setPreferredSize(new Dimension(1500, 700));
		return container;
	}

	
	/**
	 * Method to create the text of the panel
	 * 
	 * @param pass pass to set the text of
	 * @return JPanel created
	 */
	public JPanel setText(Pass pass) {
		this.zone=pass.getZone();
		this.price=pass.getPrice();
		
		JPanel container = new JPanel();
		container.setLayout(new GridLayout(0, 1));

		JLabel label1 = new JLabel(pass.getName());
		label1.setFont(label1.getFont().deriveFont(128.0f));
		
		container.add(label1);
		JTextArea text = new JTextArea("Plays: ", 80, 80);
		text.setEditable(false);
		;
		for (Event e : ((CyclePass) pass).getCycle().getEvents()) {
			text.append("\n	" + e.getTitle());
		}
		
		text.setFont(text.getFont().deriveFont(28.0f));

		JScrollPane scroll = new JScrollPane(text, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);

	
		text.setFont(text.getFont().deriveFont(28.0f));
		
		JLabel zone =new JLabel("Zone : "+this.zone.getName());
		JLabel price =new JLabel("Price : "+this.price);
		
		container.add(scroll);
		container.add(zone);
		container.add(price);
			
		container.setPreferredSize(new Dimension(1500, 700));
		return container;
	}

	/**
	 * Method to add a listener for the back button
	 * 
	 * @param button button to add the listener 
	 * @param parent main frame
	 * @param app containing all the information of the application
	 */
	public static void addListener(JButton button, MainFrame parent, TheaterApp app) {
		button.addActionListener(e -> {
			button.setBackground(Color.BLUE);

			parent.changeView(new MainPanel(parent, app));

		});
	}
	
	/**
	 * Method to change to admin mode
	 * 
	 * @param p pass to create 
	 * @param parent main frame
	 * @param app containing all the information of the application
	 * @return a panel with all the contents
	 */
	public JPanel adminMode(Pass p, MainFrame parent, TheaterApp app) {
		JPanel view = new JPanel();
		view.setLayout(new GridLayout(0, 1));
		view.add(new AdminInterface(parent, app));
		JPanel passSpecific = new JPanel();
		
		JTextField name = new JTextField(p.getName());
		name.setFont(name.getFont().deriveFont(128.0f));

		view.add(name);
		
		passSpecific.setLayout(new FlowLayout());
		JLabel zoneLabel = new JLabel("Zone : ");
		JComboBox<String> zones = new JComboBox<String>();
		for(Zone z : app.getUsableZones()) {
			zones.addItem(z.getName());
		}
		
		JLabel discountLabel = new JLabel("Discount : ");
		JTextField discount = new JTextField(3);
		discount.setText(String.valueOf(((CyclePass)p).getDiscountPercentage()));
		passSpecific.add(zoneLabel);
		passSpecific.add(zones);
		passSpecific.add(discountLabel);
		passSpecific.add(discount);


		JPanel buttons = new JPanel();
		
		
		JButton save = new JButton("SAVE CHANGES");
		JButton deletePass = new JButton("DELETE PASS");
		buttons.add(deletePass);
		buttons.add(save);
		

		save.addActionListener(e->{
			((CyclePass)p).changePass(name.getText(), Integer.parseInt(discount.getText()), app.getZone((String)zones.getSelectedItem()));
			JOptionPane.showMessageDialog(save, "Pass "+p.getName()+" modified");
			parent.changeView(new MainPanel(parent, app));
		});
		
		deletePass.addActionListener(e->{
			app.getPasses().remove(p);
			JOptionPane.showMessageDialog(deletePass, "Pass "+p.getName()+" deleted");
			parent.changeView(new MainPanel(parent, app));
		});

		
		

		view.add(passSpecific);
		view.add(buttons);
		
		return view;
		
	}

}
