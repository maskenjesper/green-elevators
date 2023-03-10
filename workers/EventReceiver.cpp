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
        Request* request;
        switch (eventType) {
            case FloorButton:
                request = new Request(eventDesc.fbp.floor,
                                      0,
                                   eventDesc.fbp.type == GoingUp ? UP : DOWN,
                                      PICKUP);
                ElevatorController::addStop(ElevatorController::lowestCost(*request), *request);
                delete request;
                break;
            case CabinButton:
                if (eventDesc.cbp.floor == 32000) {
                    ElevatorController::emergencyStop(eventDesc.cbp.cabin);
                    break;
                }
                request = new Request(eventDesc.cbp.floor,
                                      eventDesc.cbp.cabin,
                                      NONE,
                                      DROPOFF);
                ElevatorController::addStop(request->cabin, *request);
                delete request;
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