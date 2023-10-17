from abc import ABC, abstractmethod

# Basic class exercises
# Create and complete Vehicle class and subclasses to satisfy tests.

# define the Vehicle class
class Vehicle(ABC):
    make = ""
    model = ""
    color = ""
    value = 0.0

    def description(self):
        desc_str = "%s %s is a %s %s worth $%.2f" % (self.make, self.model, self.color, self.type(), self.value)
        return desc_str

    
# Provided simple test() function used in main() to print
# what each function returns vs. what it's supposed to return.
def test(got, expected):
    if got == expected:
        prefix = ' OK '
    else:
        prefix = '  X '
    print('%s got: %s expected: %s' % (prefix, repr(got), repr(expected)))

# Create different objects and validate assignments.
def main():
    vehicle1 = Car(make="Seat", model="Leon", value=1000.0, color="red")
    test(vehicle1.description(), 'Seat Leon is a red Car worth $1000.00')

    vehicle2 = Motorcycle("Ducati", "Diavel 1260", value=900.25, color="black")
    test(vehicle2.description(), 'Ducati Diavel 1260 is a black Motorcycle worth $900.25')

# Standard boilerplate to call the main() function.
if __name__ == '__main__':
    main()
