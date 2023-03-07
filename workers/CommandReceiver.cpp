#include "CommandReceiver.h"

ActionQueue *CommandReceiver::actionQueue;

pthread_t CommandReceiver::init(ActionQueue *actionQueue) {
    CommandReceiver::actionQueue = actionQueue;
    pthread_t tid;
    pthread_create(&tid, NULL, worker, NULL);
    return tid;
}

void *CommandReceiver::worker(void *) {
    while (true) {
        EventDesc eventDesc;
        EventType eventType = waitForEvent(&eventDesc);
        std::string eventName;
        switch (eventType) {
            case FloorButton:
                eventName = "Floor Button";
                actionQueue->add(new Action(eventDesc.fbp.floor,
                                           0,
                                           eventDesc.fbp.type == GoingUp ?
                                                Action::UP : Action::DOWN,
                                           Action::PICKUP));
                break;
            case CabinButton:
                eventName = "Cabin Button";
                actionQueue->add(new Action(eventDesc.cbp.floor,
                                           eventDesc.cbp.cabin,
                                           Action::NONE,
                                           Action::DROPOFF));
                break;
            case Position:
                eventName = "Position";
                break;
            case Speed:
                eventName = "Speed";
                break;
            case Error:
                eventName = "Error";
                break;
        }
        std::cout << "event receiver " << eventName << std::endl;
    }
}