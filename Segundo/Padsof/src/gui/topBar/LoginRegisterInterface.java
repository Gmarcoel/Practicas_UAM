package gui.topBar;

import java.awt.*;

import java.awt.event.*;

import javax.swing.*;
import app.*;
import gui.mainform.MainFrame;
import gui.mainform.MainPanel;

/**
 * This is a class that allow us to create the manage theater interface
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class LoginRegisterInterface extends JPanel {
	/**
	 * Method to create login and register interface
	 * 
	 * @param parent main frame
	 * @param app containing all the info of the app
	 */
	public LoginRegisterInterface(MainFrame parent, TheaterApp app) {

		this.setLayout(new FlowLayout(FlowLayout.RIGHT)); // Create the layout

		JPanel register = new JPanel();
		JPanel login = new JPanel();

		JLabel usernameLogin = new JLabel("Enter username: "); // Create the label username
		JLabel passwordLogin = new JLabel("Enter password: "); // Create the label username
		final JTextField fieldUserLogin = new JTextField(10); // Create the textfield
		final JPasswordField fieldPasswordLogin = new JPasswordField(10); // Create the textfield
		JButton loginButton = new JButton("Login");
		JTabbedPane tabs = new JTabbedPane();

		tabs.addTab("Register", register);
		tabs.addTab("Login", login);

		login.add(usernameLogin);
		login.add(fieldUserLogin);
		login.add(passwordLogin);
		login.add(fieldPasswordLogin);
		login.add(loginButton);

		JLabel usernameRegister = new JLabel("Enter username: "); // Create the label username
		JLabel passwordRegister = new JLabel("Enter password: "); // Create the label username
		final JTextField fieldUserRegister = new JTextField(10); // Create the textfield
		final JPasswordField fieldPasswordRegister = new JPasswordField(10); // Create the textfield
		JButton registerButton = new JButton("Register");

		register.add(usernameRegister);
		register.add(fieldUserRegister);
		register.add(passwordRegister);
		register.add(fieldPasswordRegister);
		register.add(registerButton);

		loginButton.addActionListener(e -> {
			boolean outcome = app.logIn(fieldUserLogin.getText(), String.valueOf(fieldPasswordLogin.getPassword()));
			if (outcome == true) {
				loginButton.setBackground(Color.GREEN);
				JOptionPane.showMessageDialog(loginButton, "You have logged in");
				parent.setLoged(true);
				parent.setCurrentUser(fieldUserLogin.getText());
				parent.changeView(new MainPanel(parent, app));
			} else {
				loginButton.setBackground(Color.RED);
				JOptionPane.showMessageDialog(loginButton, "Login unsuccessfull, check your credentials");
			}
		});

		registerButton.addActionListener(e -> {
			if (fieldUserRegister.getText().isEmpty() || fieldPasswordRegister.getPassword().length == 0) {
				registerButton.setBackground(Color.RED);
				JOptionPane.showMessageDialog(registerButton, "Username or password are invalid");

			} else {
				boolean outcome = app.register(fieldUserRegister.getText(),
						String.valueOf(fieldPasswordRegister.getPassword()));
				if (outcome == true) {
					registerButton.setBackground(Color.GREEN);
					JOptionPane.showMessageDialog(registerButton, "You have registered");
					parent.setCurrentUser(fieldUserRegister.getText());
					parent.setLoged(true);
					parent.changeView(new MainPanel(parent, app));
				} else {
					registerButton.setBackground(Color.RED);
					JOptionPane.showMessageDialog(registerButton, "Another user with that username alreay exists");
				}
			}
		});

		tabs.setSelectedIndex(0);
		this.add(tabs);

	}

}
