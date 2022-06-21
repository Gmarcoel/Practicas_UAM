package gui.mainform;

import javax.swing.*;

import app.*;
import users.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.*;
import java.time.*;
import java.util.*;
/**
 * This is a class that allow us to create the main frame
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class MainFrame extends JFrame {
	private JPanel panels;
	private TheaterApp app;
	private MainPanel card1;
	private String currentUser;
	private boolean loged = false;

	/**
	 * Method to create the main frame
	 * 
	 */
	public MainFrame() {
		try {
			this.app = loader();
		} catch (FileNotFoundException fnfe) {
			System.out.println("Exception: " + fnfe);
		} catch (IOException ioe) {
			System.out.println("Exception: " + ioe);
		} catch (ClassNotFoundException cnfe) {
			System.out.println("Exception: " + cnfe);
		}

<<<<<<< HEAD
		this.card1 = new MainPanel(this, this.app);
=======
		// Check booking
		ArrayList<Customer> victims = this.app.updateBookings();
	
		

        this.card1 = new MainPanel(this, this.app);
>>>>>>> 1cd9b5ca3eae2f21b66106514195f08a9f18320b
		this.panels = new JPanel(new CardLayout());
		this.panels.add(this.card1, "Events");
		panels.setVisible(true);
		this.setContentPane(panels);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(1600, 900);
		this.setVisible(true);

		this.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {

				try {
					app.save();
				} catch (FileNotFoundException fnfe) {
					System.out.println("Exception: " + fnfe);
				} catch (IOException ioe) {
					System.out.println("Exception: " + ioe);
				}
				System.exit(0);

			}

		});
	}

	/**
	 * Method to load all the information of a theater app previously stored
	 * 
	 * @return app at the point where it was stored
	 * @throws FileNotFoundException  exception
	 * @throws IOException            exception
	 * @throws ClassNotFoundException exception
	 */
	private static TheaterApp loader() throws FileNotFoundException, IOException, ClassNotFoundException {
		ObjectInputStream in = new ObjectInputStream(new FileInputStream("./obj/" + "app" + ".objectData"));
		Object object = in.readObject();
		TheaterApp app = (TheaterApp) object;
		in.close();
		app.load();

		return app;
	}

	/**
	 * Method to change the view
	 * 
	 * @param p panel to be substituted
	 */
	public void changeView(JPanel p) {
		this.panels.removeAll();
		this.panels.add(p);
		this.panels.repaint();
		this.panels.revalidate();
	}

	/**
	 * Method to set the current user
	 * 
	 * @param u string with the name of the user
	 */
	public void setCurrentUser(String u) {
		this.currentUser = u;
	}

	/**
	 * Method to get the current user
	 * 
	 * @return string with the name of the user
	 */
	public String getCurrentUser() {
		return this.currentUser;
	}

	/**
	 * Method to set the logged value
	 * 
	 * @param u boolean value to set if logged
	 */
	public void setLoged(boolean u) {
		this.loged = u;
	}

	/**
	 * Method to get if logged
	 * 
	 * @return boolean if logged
	 */
	public boolean getLoged() {
		return this.loged;
	}

}