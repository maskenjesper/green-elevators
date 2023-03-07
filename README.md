# Green Elevators
Controller for green elevators

command to run the elevator application:
java -classpath ElevatorsApp/elevator/lib/elevator.jar -Djava.security.policy=ElevatorsApp/elevator/lib/rmi.policy -Djava.rmi.server.codebase=file:d:ElevatorsApp/elevator/lib/elevator.jar elevator.Elevators -top 5 -number 5 -tcp
java -jar elevator.jar

java -classpath lib/elevator.jar -Djava.security.policy=lib/rmi.policy -Djava.rmi.server.codebase=file:d:lib/elevator.jar elevator.Elevators -top 5 -number 5 -tcp
