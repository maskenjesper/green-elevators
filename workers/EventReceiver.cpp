#include <cmath>
#include "EventReceiver.h"

pthread_t EventReceiver::tid;

void EventReceiver::init() {
    pthread_create(&tid, NULL, worker, NULL);
}

void EventReceiver::quit() {
    pthread_join(tid, nullptr);
}

void *EventReceiver::worker(void *) {
    while (true) {
        EventDesc eventDesc;
        EventType eventType = waitForEvent(&eventDesc);
        Action* action;
        switch (eventType) {
            case FloorButton:
                action = new Action(eventDesc.fbp.floor,
                                   0,
                                   eventDesc.fbp.type == GoingUp ? UP : DOWN,
                                   PICKUP);
                ElevatorController::addStop(ElevatorController::lowestCost(*action), *action);
                break;
            case CabinButton:
                if (eventDesc.cbp.floor == 32000) {
                    ElevatorController::emergencyStop(eventDesc.cbp.cabin);
                    break;
                }
                action = new Action(eventDesc.cbp.floor,
                                   eventDesc.cbp.cabin,
                                   NONE,
                                   DROPOFF);
                ElevatorController::addStop(action->elevator, *action);
                break;
            case Position:
                ElevatorController::updatePosition(eventDesc.cp.cabin, eventDesc.cp.position);
                break;
            case Speed:
                ElevatorController::updateSpeed(eventDesc.s.speed);
                break;
            case Error:
                std::cout << "Error event: " << eventDesc.e.str << std::endl;
                break;
        }
    }
}