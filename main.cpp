#include <iostream>

#include "utils/hardwareAPI.h"
#include "workers/EventReceiver.h"
#include "workers/ElevatorController.h"
#include "utils/CommandSender.h"

int main(int argc, char *argv[]) {
    int cabins = argc > 1 ? atoi(argv[1]) : 5;
    int floors = argc > 2 ? atoi(argv[2]) : 6;

    std::cout << "Using " << cabins << " cabins" << std::endl;
    std::cout << "Using " << floors << " floors" << std::endl;

    initHW((char*) "127.0.0.1", 4711);
    CommandSender::init();

    ElevatorController::init(cabins, floors);
    EventReceiver::init();

    EventReceiver::quit();
    ElevatorController::quit();
}
