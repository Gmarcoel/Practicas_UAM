package gui.topBar;

import java.awt.*;

import java.awt.event.*;

import javax.swing.*;
import app.*;
import gui.cycles.CreateCyclePanel;
import gui.events.CreateEventPanel;
import gui.mainform.MainFrame;
import gui.mainform.MainPanel;
import gui.manage.ManageTheaterPanel;
import gui.manage.StatisticsInterface;

/**
 * This is a class that allow us to create the manage theater interface
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class AdminInterface extends JPanel{

    /**
	 * Method to create the admin interface
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 */
	public AdminInterface (MainFrame parent, TheaterApp app){

        this.setLayout(new FlowLayout(FlowLayout.RIGHT)); // Create the layout

        JButton logOut= new JButton("Log Out");
        		logOut.setBackground(Color.red);
        		logOut.setForeground(Color.white);
        JButton statistics= new JButton("Statistics");
		statistics.setBackground(new Color(21,45,69));
		statistics.setForeground(Color.white);
        JButton createEvent= new JButton("Create Event");
		createEvent.setBackground(new Color(21,45,69));
		createEvent.setForeground(Color.white);
        JButton createCycle= new JButton("Create Cycle");
		createCycle.setBackground(new Color(21,45,69));
		createCycle.setForeground(Color.white);
        JButton manage= new JButton("Manage");
		manage.setBackground(new Color(21,45,69));
		manage.setForeground(Color.white);
        JButton home= new JButton("Home");
		home.setBackground(new Color(21,45,69));
		home.setForeground(Color.white);
        
        
        logOut.addActionListener(e->{
                parent.setCurrentUser(null);
                parent.setLoged(false);
                parent.changeView(new MainPanel(parent, app));
        	});
        
        statistics.addActionListener(e->{
            parent.changeView(new StatisticsInterface(parent, app));
    	});

        home.addActionListener(e->{
                parent.changeView(new MainPanel(parent, app));
        	});

        createEvent.addActionListener(e->{
                parent.changeView(new CreateEventPanel(parent, app));
        	});

        createCycle.addActionListener(e->{
            parent.changeView(new CreateCyclePanel(parent, app));
    	});
        
        manage.addActionListener(e->{
            parent.changeView(new ManageTheaterPanel(parent, app));
    	});


        this.add(home);
        this.add(createEvent);
        this.add(createCycle);
        this.add(manage);
        this.add(statistics); 
        this.add(logOut);
        
        
	}
	
	
	
}
