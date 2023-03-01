# Green Elevators

command to run the elevator application:
java -classpath ElevatorsApp/elevator/lib/elevator.jar -Djava.security.policy=ElevatorsApp/elevator/lib/rmi.policy -Djava.rmi.server.codebase=file:d:ElevatorsApp/elevator/lib/elevator.jar elevator.Elevators -top 5 -number 5 -tcp
