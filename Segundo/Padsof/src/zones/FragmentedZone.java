package zones;

import java.util.*;

/**
 * This is a class that allow us to create a fragmented zone
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier López de la Nieta Luján
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class FragmentedZone extends Zone {
	private ArrayList<Zone> subzones = null;

	/**
	 * Constructor, with the attributes
	 * 
	 * @param name string with the name of the zone
	 */
	public FragmentedZone(String name) {
		super(name);
		if (name.isBlank()) {
			System.out.println("Error: Invalid name\n");
			return;
		}
		subzones = new ArrayList<Zone>();
	}

	/**
	 * Method to add a new subzone to the fragmente zone
	 * 
	 * @param subzone to be added in the fragmented zone
	 */
	public void addSubzone(Zone subzone) {
		if (subzone == null) {
			System.out.println("Error: Invalid subzone in addSubzone\n");
			return;
		}
		subzones.add(subzone);
		return;
	}

	/**
	 * Method to get the attendees of the fragmented zone
	 * 
	 * @return int with the number of attendees
	 */
	@Override
	public int getAttendees() {
		if (this.subzones.isEmpty()) {
			System.out.println("Error: No subzones in getAttendees for" + this.getName());
			return 0;
		}
		int n = 0;
		for (Zone z : this.subzones) {
			n += z.getAttendees();
		}
		return n;
	}

	/**
	 * Method to get the occupancy percentage of the fragmented zone
	 * 
	 * @return int with percentage of occupancy
	 */
	@Override
	public int getOccupancy() {
		if (this.subzones.isEmpty()) {
			System.out.println("Error: No subzones in getOccupancy\n");
			return 100;
		}
		double available = 0;
		double all = 0;
		for (Zone z : this.subzones) {
			available += z.getNPosPeople();
			all += z.getNMaxPeople();
		}
		return (int) ((available * 100) / all);
	}

	/**
	 * Method to get the maximum number of people of the fragmented zone
	 * 
	 * @return int with the maximum number of people
	 */
	@Override
	public int getNMaxPeople() {
		if (this.subzones.isEmpty()) {
			System.out.println("Error: No subzones in getNMaxPeoplefor" + this.getName());
			return 0;
		}
		int i = 0;
		for (Zone z : this.subzones) {
			if (z instanceof FragmentedZone) {
				i += ((FragmentedZone) z).getNMaxPeople();
			} else if (z instanceof SittingZone) {
				i += ((SittingZone) z).getNMaxPeople();
			} else {
				i += ((StandingZone) z).getNMaxPeople();
			}
		}
		return i;
	}

	/**
	 * Method to get the number of possible people in a fragmented zone
	 * 
	 * @return int with the number of possible people
	 */
	public int getNPosPeople() {
		if (this.subzones.isEmpty()) {
			System.out.println("Error: No subzones ingetNPosPeoplefor" + this.getName());
			return 0;
		}
		double sum = 0;
		for (Zone z : this.subzones) {
			sum += z.getNPosPeople();
		}
		return (int) (sum);
	}

	/**
	 * Method to get the subzones of the fragmented zone
	 * 
	 * @return arraylist with the subzones
	 */
	public ArrayList<Zone> getSubZones() {
		return this.subzones;
	}

	/**
	 * Method to get a subzone given a name
	 * 
	 * @param zoneName with name of the zone wanted
	 * @return zone with the name given
	 */
	public Zone getSubZone(String zoneName) {
		if (zoneName == null) {
			return null;
		}
		for (Zone zone : this.subzones) {
			if (zone instanceof FragmentedZone) {
				if (((FragmentedZone) zone).getSubZone(zoneName) != null) {
					return ((FragmentedZone) zone).getSubZone(zoneName);

				}
			}
			if (zoneName.equals(zone.getName())) {
				return zone;
			}
		}
		return null;
	}

	/**
	 * return all usable subzones
	 * 
	 * @return arraylist of zones
	 */
	public ArrayList<Zone> getUsableSubZones() {
		ArrayList<Zone> zs = new ArrayList<>();
		for (Zone zone : this.subzones) {
			if (zone instanceof FragmentedZone) {
				for (Zone sz : ((FragmentedZone) zone).getUsableSubZones()) {
					zs.add(sz);
				}
			} else {
				zs.add(zone);
			}

		}
		return zs;
	}
	/**
	 * return all subzones
	 * 
	 * @return arraylist of zones
	 */
	public ArrayList<Zone> getAllSubZones() {
		ArrayList<Zone> zs = new ArrayList<>();
		for (Zone zone : this.subzones) {
			if (zone instanceof FragmentedZone) {
				for (Zone sz : ((FragmentedZone) zone).getAllSubZones()) {
					zs.add(sz);
				}
			}
				zs.add(zone);
			

		}
		return zs;
	}

	/**
	 * Method that checks if a seat inside a fragmented zone is occupied
	 * 
	 * @param zone containing the seat to check
	 * @param seat to be checked
	 * @return boolean if the seat is occupied
	 */
	public boolean isOccupied(Zone zone, Seat seat) {
		if (this.subzones.isEmpty()) {
			System.out.println("Error: No subzones in isOccupied\n");
			return true;
		} else if (zone == null) {
			System.out.println("Error: Invalid zone\n");
			return true;
		} else if (seat == null) {
			System.out.println("Error: Invalid seat\n");
			return true;
		}
		for (Zone z : this.subzones) {
			if (z instanceof FragmentedZone) {
				if (!((FragmentedZone) z).isOccupied(zone, seat))
					return false;
			}
			if (z.getName().equals(zone.getName())) {
				return ((SittingZone) z).isOccupied(seat);
			}
		}
		return true;
	}

	/**
	 * Method that checks if a standing zone inside a fragmented zone is fully
	 * occupied
	 * 
	 * @param zone to check
	 * @return boolean if the zone is fully occupied
	 */
	public boolean isOccupied(Zone zone) {
		if (zone == null) {
			System.out.println("Error: Invalid zone\n");
			return true;
		}
		for (Zone z : this.subzones) {
			if (z instanceof FragmentedZone) {
				if (!((FragmentedZone) z).isOccupied(zone))
					return false;
			}
			if (z.getName().equals(zone.getName())) {
				return ((StandingZone) z).isOccupied();
			}
		}
		return true;
	}

	/**
	 * Method to occupy a single space in a zone inside a fragmented zone
	 * 
	 * @param zone to be occupied
	 */
	public void occupy(Zone zone) {
		if (zone == null) {
			System.out.println("Error: Invalid zone\n");
			return;
		}
		for (Zone z : this.subzones) {
			if (z instanceof FragmentedZone) {
				((FragmentedZone) z).occupy(zone);
				return;
			}
			if (z.getName().equals(zone.getName())) {
				z.occupy();
				return;
			}
		}
	}

	/**
	 * Method to set the occupancy percentage of the fragmented zone
	 * 
	 * @param o with the new percentage
	 */
	@Override
	public void setOccupancy(int o) {
		if (o > 100 || o < 0) {
			System.out.println("Error: Number outside expected range\n");
			return;
		}
		for (Zone z : this.getSubZones()) {
			z.setOccupancy(o);
		}
	}

	/**
	 * Method to clone a fragmented zone
	 * 
	 * @return zone cloned
	 */
	@Override
	public Zone cloneZone() {
		FragmentedZone fz = new FragmentedZone(this.getName());
		for (Zone sz : this.getSubZones()) {
			fz.addSubzone(sz.cloneZone());
		}
		return fz;
	}

	/**
	 * Method to remove a subzone inside a fragmented zone
	 * 
	 * @param zone to be removed
	 */
	public void removeSubZone(Zone zone) {
		if (zone == null) {
			System.out.println("Error: null zone\n");
			return;
		}
		for (Zone z : this.subzones) {
			if (z.getName().equals(zone.getName())) {
				this.subzones.remove(z);
				return;
			} else if (z instanceof FragmentedZone) {
				((FragmentedZone) z).removeSubZone(zone);
			}
		}
	}
	/**
	 * returns all the fragmented zones
	 * @return array of zones
	 */
	public ArrayList<Zone> getFragmentedsubZones()	{
		ArrayList<Zone> aux = new ArrayList<Zone>();
		for (Zone z : this.subzones){
			if( z instanceof FragmentedZone)	{
				FragmentedZone fz = (FragmentedZone) z;
				aux.add(fz);
				aux.addAll(fz.getFragmentedsubZones());
			}
		}
		return aux;
	}
}
