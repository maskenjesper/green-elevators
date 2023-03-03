#include "CommandReceiver.h"

pthread_t CommandReceiver::init() {
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
                break;
            case CabinButton:
                eventName = "Cabin Button";
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