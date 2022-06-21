package gui.events;

import app.TheaterApp;

import events.Event;
import events.Price;
import gui.mainform.MainFrame;
import gui.mainform.MainPanel;
import gui.payments.PayPanel;
import performances.Performance;
import performances.Ticket;
import users.Customer;
import users.RegisteredUser;
import zones.*;

import java.awt.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

/**
 * This is a class that allow us to create the event butrton
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class EventInterface extends JPanel {
	private Performance p = null;
	private Zone z = null;
	private Seat seat = null;
	private JComboBox<LocalDateTime> performances;

	/**
	 * Class constructor
	 * 
	 * @param event  event
	 * @param parent Mainframe
	 * @param app    theaterapp
	 */
	EventInterface(Event event, MainFrame parent, TheaterApp app) {

		JPanel container = setText(event, parent, app);

		JButton button = new JButton("Back");
		button.setPreferredSize(new Dimension(80, 60));
		addListener(button, parent, app);
		this.performances = new JComboBox<LocalDateTime>(passesToLocalDateTime(event, parent, app));
		JPanel subContainer = new JPanel();
		subContainer.setLayout(new BorderLayout());
		subContainer.add(button, BorderLayout.EAST);

		// PerformancePanel performances = new PerformancePanel(event, parent, app);

		performances.addActionListener(e -> {
			this.p = event.getPerformance((LocalDateTime) performances.getSelectedItem());
		});
		if (parent.getLoged() == true && !(parent.getCurrentUser().equals("admin"))) {
			if (this.p != null && this.p.checkIfFull() == true) {
				subContainer.add(performances, BorderLayout.WEST);

				JButton waitlist = new JButton("SUBSCRIBE TO WAITLIST");
				waitlist.addActionListener(e -> {
					if (p.getWaitList().getCustomers().contains(app.getCustomer(parent.getCurrentUser()))) {
						JOptionPane.showMessageDialog(null, "First choose zone and performance!");
					} else {
						app.suscribeToWaitList((Customer) app.getCustomer(parent.getCurrentUser()), p);
						JOptionPane.showMessageDialog(null, "You subscribed to the waitlist, wait to be notified");

					}
				});

				subContainer.add(waitlist, BorderLayout.CENTER);
			} else {
				// El de south->west se divide en dos,
				JPanel southWest = new JPanel();
				southWest.setLayout(new FlowLayout());

				// Se crea las zonas
				// UsableZonePanel zones = new UsableZonePanel(app);
				// zones.setPreferredSize(new Dimension(450, 120));
				// Zone z = zones.getZone();

				ArrayList<String> names = new ArrayList<>();
				for (Zone z : app.getUsableZones()) {

					names.add(z.getName());
				}
				String s[] = new String[names.size()];
				s = names.toArray(s);

				JList<String> zonesString = new JList<String>(s);
				zonesString.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
				zonesString.setFont(zonesString.getFont().deriveFont(28.0f));

				JScrollPane zones = new JScrollPane(zonesString);
				zones.setPreferredSize(new Dimension(450, 120));
				zones.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
				zones.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
				// zones.add(scrollPane);

				// Zone z = app.getZone((String)zonesString.getSelectedValue());
				zonesString.addListSelectionListener(x -> {
					if (zonesString.getValueIsAdjusting() == false) {
						this.z = app.getZone((String) zonesString.getSelectedValue());
						southWest.removeAll();
						southWest.add(zones);
						southWest.add(performances);

						// Se añade el todo mal
						if (this.z instanceof SittingZone) {
							this.seat = null;
							SittingZone sz = (SittingZone) event
									.getPerformance((LocalDateTime) performances.getSelectedItem()).getZone(z);
							ArrayList<String> seats = new ArrayList<>();
							JLabel sub = new JLabel();
							ArrayList<Seat> seatList = new ArrayList<>();
							for (int i = 0; i < sz.getNRows(); i++) {
								for (int j = 0; j < sz.getNColumns(); j++) {

									// System.out.println("R: " + (sz.getSeat(i, j)).getNRow() + " C: " +
									// (sz.getSeat(i, j)).getNColumn() + " is " +
									// (sz.getMatrix()[i][j]).getAvailable());

									if (sz.isAvailable(i, j) == true) {
										// if (sz.isOccupied((sz.getMatrix()[i][j])) == false) {
										seats.add("Row:" + (sz.getMatrix()[i][j]).getNRow() + " Column: "
												+ (sz.getMatrix()[i][j]).getNColumn());
										seatList.add(sz.getSeat(i, j));
									}
								}
							}

							if (!seats.isEmpty()) {

								String[] str = new String[seats.size()];
								str = seats.toArray(str);
								JComboBox<String> passBox = new JComboBox<String>(str);

								passBox.addActionListener(e -> {
									this.seat = seatList.get(passBox.getSelectedIndex());
								});

								southWest.add(passBox);
								southWest.repaint();
								subContainer.repaint();
								container.repaint();
								container.revalidate();
							}
						}
					}
					southWest.repaint();
					subContainer.repaint();
					container.repaint();
					container.revalidate();
				});

				// Se crean las performances

				// Se añaden zonas y performances
				southWest.add(zones);
				southWest.add(performances);

				// Inclute el southwest
				subContainer.add(southWest, BorderLayout.WEST);

				JPanel buttons = new JPanel();
				subContainer.add(buttons, BorderLayout.CENTER);
				buttons.setLayout(new BorderLayout());

				// Se crea el botón de compra
				JButton b2 = new JButton("Buy");
				b2.setFont(b2.getFont().deriveFont(56.0f));
				b2.setBackground(new Color(204, 204, 204));

				buttons.add(b2, BorderLayout.CENTER);

				b2.addActionListener(e -> {
					Zone ticketZone = null;
					if (this.p != null && this.z != null) {
						ticketZone = this.p.getZone(this.z);
					} else {
						b2.setBackground(Color.RED);
						JOptionPane.showMessageDialog(null, "Please select Performance and Zone");
					}
					if (ticketZone instanceof StandingZone) {
						StandingZone sz = (StandingZone) ticketZone;

						if (sz.getNPeople() >= sz.getNPosPeople()) {
							b2.setBackground(Color.RED);
							JOptionPane.showMessageDialog(null, "Zone is full !");
						} else {
							Ticket ticket = this.p.selectTicket(ticketZone);
							if (ticket == null) {
								b2.setBackground(Color.RED);
								JOptionPane.showMessageDialog(null, "This seat is not available");
							} else {
								b2.setBackground(Color.BLUE);
								parent.changeView(new PayPanel(parent, app, ticket));
							}
						}

					} else if (ticketZone instanceof SittingZone) {
						System.out.println("Row " + this.seat.getNRow() + "Column " + this.seat.getNColumn()
								+ this.p.getEventTitle() + this.p.getDate() + "   " + ticketZone.getName());
						SittingZone stz = (SittingZone) ticketZone;

						if (stz.getAttendees() >= stz.getNPosPeople()) {
							b2.setBackground(Color.RED);
							JOptionPane.showMessageDialog(null, "Zone is full");
						} else {
							Ticket ticket2 = this.p.selectTicket(ticketZone, this.seat);
							if (ticket2 == null) {
								b2.setBackground(Color.RED);
								JOptionPane.showMessageDialog(null, "This seat is not available");
							} else {
								b2.setBackground(Color.BLUE);
								parent.changeView(new PayPanel(parent, app, ticket2));
							}
						}
					}
				});

				JButton b3 = new JButton("Book");
				b3.setFont(b3.getFont().deriveFont(56.0f));
				b3.setBackground(new Color(204, 204, 204));
				buttons.add(b3, BorderLayout.WEST);

				b3.addActionListener(e -> {
					Zone ticketZone = null;
					if (this.p != null && this.z != null) {
						ticketZone = this.p.getZone(this.z);
					} else {
						b3.setBackground(Color.RED);
						JOptionPane.showMessageDialog(null, "Please select Performance and Zone");
					}
					if (ticketZone instanceof StandingZone) {
						StandingZone sz = (StandingZone) ticketZone;

						if (sz.getNPeople() >= sz.getNPosPeople()) {
							b3.setBackground(Color.RED);
							JOptionPane.showMessageDialog(null, "Zone is full");
						} else {
							Ticket ticket = this.p.selectTicket(ticketZone);
							if (ticket == null) {
								b3.setBackground(Color.RED);
								JOptionPane.showMessageDialog(null, "This seat is not available");
							} else {
								b3.setBackground(Color.BLUE);
								JOptionPane.showMessageDialog(null, "Ticket booked");
								Customer c = (Customer) app.getCustomer(parent.getCurrentUser());
								app.bookTicket(c, ticket);
								parent.changeView(new TicketsPanelUser(parent, app));
							}
						}

					} else if (ticketZone instanceof SittingZone) {
						System.out.println("Row " + this.seat.getNRow() + "Column " + this.seat.getNColumn()
								+ this.p.getEventTitle() + this.p.getDate() + "   " + ticketZone.getName());
						SittingZone stz = (SittingZone) ticketZone;

						if (stz.getAttendees() >= stz.getNPosPeople()) {
							b3.setBackground(Color.RED);
							JOptionPane.showMessageDialog(null, "Zone is full !");
						} else {
							Ticket ticket2 = this.p.selectTicket(ticketZone, this.seat);
							if (ticket2 == null) {
								b3.setBackground(Color.RED);
								JOptionPane.showMessageDialog(null, "This seat is not available");
							} else {
								b3.setBackground(Color.BLUE);
								Customer c = (Customer) app.getCustomer(parent.getCurrentUser());
								app.bookTicket(c, ticket2);
								JOptionPane.showMessageDialog(null, "Ticket booked");
								parent.changeView(new TicketsPanelUser(parent, app));
							}
						}
					}
				});
			}

		} else if (parent.getLoged() == false) {
			subContainer.add(performances, BorderLayout.WEST);
		} else {
			JPanel buttons = new JPanel();
			buttons.setLayout(new FlowLayout());
			JButton editPerformance = new JButton("Edit performance");
			JButton deleteEvent = new JButton("Delete Event");
			editPerformance.addActionListener(e -> {
				if (this.p != null) {
					editPerformance.setBackground(Color.BLUE);
					parent.changeView(new PerformancePanel(this.p, parent, app));
				} else {
					editPerformance.setBackground(Color.RED);
					JOptionPane.showMessageDialog(null, "Please select Performance");
				}
			});

			deleteEvent.addActionListener(e -> {
				app.cancelEvent(event);
				JOptionPane.showMessageDialog(null, "Event Deleted");
				parent.changeView(new MainPanel(parent, app));
			});

			buttons.add(editPerformance);
			buttons.add(deleteEvent);

			subContainer.add(buttons, BorderLayout.CENTER);
			subContainer.add(performances, BorderLayout.WEST);
		}
		container.add(subContainer, BorderLayout.SOUTH);

		this.add(container);

	}

	/**
	 * passes to local date time all the event performances
	 * 
	 * @param event  event to create text for
	 * @param parent mainframe
	 * @param app    theater app
	 * @return an array with the dates
	 */
	public LocalDateTime[] passesToLocalDateTime(Event event, MainFrame parent, TheaterApp app) {
		ArrayList<LocalDateTime> output = new ArrayList<>();
		if (event.getPerformances() == null)
			return null;
		for (Performance p : event.getPerformances()) {
			output.add(p.getDate());
		}

		LocalDateTime d[] = new LocalDateTime[output.size()];
		d = output.toArray(d);
		return d;

	}

	/**
	 * Set text for the event
	 * 
	 * @param event  event to create text for
	 * @param parent mainframe
	 * @param app    theater app
	 * @return a panel with the content
	 */
	public JPanel setText(Event event, MainFrame parent, TheaterApp app) {
		JPanel container = new JPanel();
		container.setLayout(new BorderLayout());

		JLabel label1 = new JLabel(event.getTitle());
		label1.setFont(label1.getFont().deriveFont(128.0f));

		JTextArea text = new JTextArea("Author: " + event.getAuthor() + "\n" + "Director: " + event.getDirector() + "\n"
				+ "Description: " + event.getDescription() + "\n" + "Duration: " + event.getDuration(), 10, 30);
		text.setFont(text.getFont().deriveFont(28.0f));
		text.setEditable(false);

		JPanel addPerformance = new JPanel();

		if (parent.getLoged() == true && parent.getCurrentUser().equals("admin")) {
			// Creating a performance panel
			JPanel top = new JPanel();
			top.setLayout(new FlowLayout());
			JLabel date = new JLabel("Date : ");
			final JTextField dateField = new JTextField(7);
			JLabel time = new JLabel("Time : ");
			final JTextField timeField = new JTextField(7);
			JButton addPerformanceB = new JButton("+");

			addPerformanceB.addActionListener(e -> {
				if (dateField.getText().length() != 10 || timeField.getText().length() != 5) {
					addPerformanceB.setBackground(Color.RED);
					JOptionPane.showMessageDialog(null, "Invalid date format: Date: dd/MM/yyyy Time: HH:mm");
					return;

				} else {
					DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm");
					String recieved = dateField.getText() + " " + timeField.getText();
					try {
						LocalDateTime dateTime = LocalDateTime.parse(recieved, formatter);
						if (app.createPerformance(event, dateTime) == true) {
							dateField.setText("");
							timeField.setText("");
							this.performances.removeAllItems();
							for (LocalDateTime ldt : passesToLocalDateTime(event, parent, app)) {
								this.performances.addItem(ldt);
							}

							addPerformanceB.setBackground(Color.GREEN);
							JOptionPane.showMessageDialog(null, "Performance created");
							return;
						} else {
							addPerformanceB.setBackground(Color.RED);
							JOptionPane.showMessageDialog(null, "Invalid date");
							return;
						}
					} catch (DateTimeParseException dtpe) {
						addPerformanceB.setBackground(Color.RED);
						JOptionPane.showMessageDialog(null, "Invalid date format: Date: dd/MM/yyyy Time: HH:mm");
						return;
					}
				}

			});

			addPerformance.add(date);
			addPerformance.add(dateField);
			addPerformance.add(time);
			addPerformance.add(timeField);
			addPerformance.add(addPerformanceB);

			top.add(label1);
			top.add(addPerformance);

			container.add(top, BorderLayout.NORTH);
		} else {
			container.add(label1, BorderLayout.NORTH);

		}

		container.add(text, BorderLayout.WEST);
		container.setPreferredSize(new Dimension(1500, 700));
		return container;
	}

	/**
	 * Set listener for a button
	 * 
	 * @param button button to add listener for
	 * @param parent mainframe
	 * @param app    theater app
	 */
	public static void addListener(JButton button, MainFrame parent, TheaterApp app) {
		button.addActionListener(e -> {
			button.setBackground(Color.BLUE);

			parent.changeView(new MainPanel(parent, app));

		});
	}

}
