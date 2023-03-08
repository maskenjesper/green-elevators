#include <iostream>

#include "utils/hardwareAPI.h"
#include "workers/EventReceiver.h"
#include "workers/ElevatorController.h"
#include "workers/ActionDispatcher.h"

int main(int argc, char *argv[]) {
    int cabins = argc > 1 ? atoi(argv[1]) : 5;

    initHW((char*) "127.0.0.1", 4711);

    ElevatorController::init(cabins);
    ActionDispatcher::init();
    EventReceiver::init();

    EventReceiver::quit();
    ActionDispatcher::quit();
    ElevatorController::quit();
}
