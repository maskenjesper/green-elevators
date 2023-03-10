#include <iostream>

#include "utils/hardwareAPI.h"
#include "workers/EventReceiver.h"
#include "workers/ElevatorController.h"

int main(int argc, char *argv[]) {
    int cabins = argc > 1 ? atoi(argv[1]) : 5;

    initHW((char*) "127.0.0.1", 4711);

    ElevatorController::init(cabins);
    EventReceiver::init();

    EventReceiver::quit();
    ElevatorController::quit();
}
