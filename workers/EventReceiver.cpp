#include <cmath>
#include "EventReceiver.h"

pthread_t EventReceiver::tid;
ActionQueue *EventReceiver::actionQueue;

void EventReceiver::init(ActionQueue *actionQueueArg) {
    actionQueue = actionQueueArg;
    pthread_create(&tid, NULL, worker, NULL);
}

void EventReceiver::quit() {
    pthread_join(tid, nullptr);
}

void *EventReceiver::worker(void *) {
    while (true) {
        EventDesc eventDesc;
        EventType eventType = waitForEvent(&eventDesc);
        switch (eventType) {
            case FloorButton:
                actionQueue->add(new Action(eventDesc.fbp.floor,
                                           0,
                                           eventDesc.fbp.type == GoingUp ?
                                                UP : DOWN,
                                           PICKUP));
                break;
            case CabinButton:
                actionQueue->add(new Action(eventDesc.cbp.floor,
                                           eventDesc.cbp.cabin,
                                           NONE,
                                           DROPOFF));
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