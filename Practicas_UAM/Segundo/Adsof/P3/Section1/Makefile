all: TesterLicense FineTester TesterFines Tester1 TesterITV

doc: 
	javadoc -d doc -author pr3/traffic/drivers/*.java pr3/traffic/fines/*.java pr3/traffic/vehicles/*.java  

TesterLicense: classes
	java pr3.traffic.drivers.TesterLicense

FineTester: classes
	java pr3.traffic.fines.FineTester

TesterFines: classes
	java pr3.traffic.fines.TesterFines

Tester1: classes
	java pr3.traffic.vehicles.Tester1

TesterITV: classes
	java pr3.traffic.vehicles.TesterITV

classes:
	javac ./pr3/traffic/drivers/*.java
	javac ./pr3/traffic/fines/*.java
	javac ./pr3/traffic/vehicles/*.java


clean:
	rm ./pr3/traffic/drivers/*.class
	rm ./pr3/traffic/fines/*.class
	rm ./pr3/traffic/vehicles/*.class
