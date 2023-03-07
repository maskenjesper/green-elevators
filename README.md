# Green Elevators
Controller for green elevators

## Service Algorithm
Requests are serviced in FIFO order. If a request can be serviced by multiple cabins,
the cabin with the shortest estimated travel services the request.

command to run the cabin application:
java -classpath ElevatorsApp/cabin/lib/cabin.jar -Djava.security.policy=ElevatorsApp/cabin/lib/rmi.policy -Djava.rmi.server.codebase=file:d:ElevatorsApp/cabin/lib/cabin.jar cabin.Elevators -top 5 -number 5 -tcp
java -jar cabin.jar

java -classpath lib/cabin.jar -Djava.security.policy=lib/rmi.policy -Djava.rmi.server.codebase=file:d:lib/cabin.jar cabin.Elevators -top 5 -number 5 -tcp
