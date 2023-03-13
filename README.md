# Green Elevators
Controller for green elevators

## Commands
command to run the cabin application:
java -classpath lib/cabin.jar -Djava.security.policy=lib/rmi.policy -Djava.rmi.server.codebase=file:d:lib/cabin.jar cabin.Elevators -top 5 -number 5 -tcp -precision 0.05
