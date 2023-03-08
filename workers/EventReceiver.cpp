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
        switch (eventType) {
            case FloorButton:
                std::cout << "Floor button" << std::endl;
                ActionDispatcher::addAction(new Action(eventDesc.fbp.floor,
                                           0,
                                           eventDesc.fbp.type == GoingUp ?
                                                UP : DOWN,
                                           PICKUP));
                break;
            case CabinButton:
                std::cout << "Cabin button" << std::endl;
                ActionDispatcher::addAction(new Action(eventDesc.cbp.floor,
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