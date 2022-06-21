package races;

import vehicles.*;


import java.text.DecimalFormat;
import java.util.*;

import components.IComponent;
import powerups.*;

/**
 * Class to desing the race to be used
 * 
 * @author Daniel Varela & Guillermo Martín-Coello
 *
 */
public class Race {
	private int length;
	private ArrayList<IVehicle> vehicles;
	private ArrayList<IPowerUp> powerups;
	private boolean allowAttacks = false;
	private boolean allowPowerUps = false;

	public Race(int length) {
		this.length = length;
		vehicles = new ArrayList<>();
		powerups = new ArrayList<>();
		this.powerups.add(new AttackAll(this));
		this.powerups.add(new Swap(this));
		this.powerups.add(new Shield());
	}

	public void addVehicle(IVehicle vehicle) {
		this.vehicles.add(vehicle);
	}
	/**
	 * Check if race is valid
	 * @return true if valid
	 */
	public boolean checkViability() {
		if (this.vehicles.size() < 2) {
			System.out.println("There are not enough vehicles to race\n");
			return false;
		} else if (this.vehicles.size() > 10) {
			System.out.println("There are too many vehicles to race\n");
			return false;
		}
		for (IVehicle v : this.vehicles) {
			if (this.length <= v.getMaxSpeed()) {
				System.out.println("Race too short for vehicle " + v.getName() + "\n");
				return false;
			}
		}
		return true;

	}

	/**
	 * Writes race info to output
	 * @return S
	 */
	@Override
	public String toString() {
		String output = "";
		DecimalFormat numberFormat = new DecimalFormat("#.00");

		output += "Race with maximum length: " + this.length + "\n";
		for (IVehicle v : vehicles) {
			output = output + v;
			for (IVehicle v2 : vehicles) {
				if (v2.getName() != v.getName()) {
					output = output + "     " + v.getName() + " distance to " + v2.getName() + ": "
							+ numberFormat.format(Math.abs(v.getActualPosition() - v2.getActualPosition())) + "\n";
				}

			}
			output = output + "\n";
		}
		return output;
	}

	/**
	 * Simulates the race
	 */
	public void simulate() {
		DecimalFormat numberFormat = new DecimalFormat("#.00");
		SplittableRandom random = new SplittableRandom();
		boolean winner = false;
		int i = 1;
		boolean canAttack = false;
		while (winner == false) {
			System.out.println("---------\nStarting Turn: " + i);
			System.out.println(this);
			if (this.allowAttacks == true && i % 3 == 0) {
				System.out.println("Starting attack fase");
				for (IVehicle v : this.vehicles) {
					for (IComponent ic : v.getComponents()) {
						if (ic.getName().equals("BananaDispenser") && ic.isDamaged() == false) {
							canAttack = true;
							if(this.getCloserVehicle(v) != null ) {
								attack(v, this.getCloserVehicle(v));
							}
							} 


					}
					if (canAttack == false) {
						System.out.println(v.getName() + " can not attack");
					}
					canAttack = false;

				}
				System.out.println("End attack fase");
			} else {
				System.out.println("Not attacking turn");
				if (this.allowPowerUps == true) {
					if (i > 3 && (random.nextInt(10) == 0)) {
						System.out.println("Turn with powerups");
						for (IVehicle iv : this.vehicles) {
							this.usePowerUp(iv);
						}
					} else {
						System.out.println("Turn with no powerups");
					}
				}
			}

			for (IVehicle v : this.vehicles) {
				for (IComponent ic : v.getComponents()) {
					if (ic.isDamaged()) {
						System.out.println(v.getName() + " " + ic.getName() + " is being repaired "
								+ (ic.costRepair() - ic.currentRepair() + 1) + "/" + ic.costRepair());
					}
				}
				v.updatePosition();
				if (v.getActualPosition() >= this.length) {
					System.out.println("\n");
					System.out.println("Ending Turn: " + i + "\n---------");
					System.out.println(v.getName() + ". Speed " + v.getMaxSpeed() + ". Actual position: "
							+ numberFormat.format(v.getActualPosition()) + ".\n has won the race");
					winner = true;
					return;
				}
			}

			System.out.println("\n");
			System.out.println("Ending Turn: " + i);
			System.out.println("---------");
			i++;

		}
	}

	/**
	 * It breaks a random component of a vehicle v with a 50% chance
	 * 
	 * @param v the vehicle you want to break a component of
	 */
	public void attack(IVehicle v, IVehicle v2) {
		SplittableRandom random = new SplittableRandom();
		IComponent comp = null;
		if(random.nextInt(2) == 0){
			comp = v2.getComponents().get(random.nextInt((v2.getComponents()).size()));
			comp.setDamaged(true);
			System.out.println(v.getName() + " attacks " + v2.getName() + " " + comp.getName());
			}
		else {
								System.out.println(v.getName() + " fails attack");
							}
	}
	/**
	 * Vehicle uses power up
	 * @param iv vehicle
	 */
	public void usePowerUp(IVehicle iv) {
		SplittableRandom random = new SplittableRandom();
		IPowerUp ip = this.powerups.get(random.nextInt(this.powerups.size()));
		ip.applyPowerUp(iv);
	}

	/**
	 * If true allow cars to attack each other
	 * 
	 * @param allowAttacks true if attacks are allowed
	 */
	public void allowAttacks(boolean allowAttacks) {
		this.allowAttacks = allowAttacks;
	}

	/**
	 * If true allow cars to have power ups
	 * 
	 * @param allowPowerUps true if power ups are allowed
	 */
	public void allowPowerUps(boolean allowPowerUps) {
		this.allowPowerUps = allowPowerUps;
	}
	/**
	 * Get the list of the vehicles of the race
	 * @return list of vehicles
	 */
	public List<IVehicle> getVehicles() {
		return this.vehicles;
	}
/**
 * Gets the closest vehicle from the given one, if two of them are at the same distance then chooses one of them randomly
 * @param v vehicle to check
 * @return closest vehicle or null if none less than 30 distance close
 */
	public IVehicle getCloserVehicle(IVehicle v) {
		double distance = 30;
		IVehicle ahead = null;
		// if ((this.getCloserVehicle(v) != null) && (random.nextInt(2) == 0))
		for (IVehicle vehicle : this.vehicles) {
			SplittableRandom random = new SplittableRandom();
			if (vehicle.getActualPosition() - v.getActualPosition() < distance
					&& vehicle.getActualPosition() - v.getActualPosition() > 0) {
				distance = vehicle.getActualPosition() - v.getActualPosition();
				ahead = vehicle;
			} else if (vehicle.getActualPosition() - v.getActualPosition() == distance
					&& vehicle.getActualPosition() - v.getActualPosition() > 0) {
				if (random.nextInt(2) == 0) {
					distance = vehicle.getActualPosition() - v.getActualPosition();
					ahead = vehicle;
				} else if (ahead == null) {
					distance = vehicle.getActualPosition() - v.getActualPosition();
					ahead = vehicle;
				}
			}
		}
		return ahead;
	}

}
