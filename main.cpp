#include <iostream>

#include "utils/hardwareAPI.h"
#include "workers/EventReceiver.h"
#include "workers/ElevatorController.h"
#include "structures/ActionQueue.h"

int main(int argc, char *argv[]) {
    int cabins = argc > 1 ? atoi(argv[1]) : 5;

    initHW((char*) "127.0.0.1", 4711);

    auto *actionQueue = new ActionQueue();

    EventReceiver::init(actionQueue);
    ElevatorController::init(actionQueue, cabins);

    EventReceiver::quit();
    ElevatorController::quit();

    delete actionQueue;
}
