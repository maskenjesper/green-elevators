
#include "ElevatorController.h"


int ElevatorController::cabins;
CabinController* ElevatorController::cabin_controllers[10];
int ElevatorController::first_cost_calculate;

void ElevatorController::init(int cabinsArg, int floors) {
    cabins = cabinsArg;
    first_cost_calculate = 0;
    for (int i = 1; i <= cabins; i++) {
        cabin_controllers[i] = new CabinController(i, floors);
        CommandSender::syncWhereIs(i);
    }
    CommandSender::syncGetSpeed();
}

void ElevatorController::quit() {
    for (int i = 1; i <= cabins; i++)
        delete cabin_controllers[i];
}

void ElevatorController::addStop(int cabin, Request request) {
    cabin_controllers[cabin]->addStop(request);
}

void ElevatorController::updatePosition(int cabin, double position) {
    cabin_controllers[cabin]->updatePosition(position);
}

void ElevatorController::updateSpeed(double speed) {
    for (int i = 1; i <= cabins; i++)
        cabin_controllers[i]->updateSpeed(speed);
}

void ElevatorController::emergencyStop(int cabin) {
    cabin_controllers[cabin]->emergencyStop();
}

int ElevatorController::lowestCost(Request request) {
    std::cout << first_cost_calculate << " ";
    first_cost_calculate = (first_cost_calculate % cabins) + 1;
    std::cout << first_cost_calculate << std::endl;
    double min = std::numeric_limits<int>::max();
    int min_cabin;
    for (int i = first_cost_calculate; i <= cabins; i++) {
        double cost = cabin_controllers[i]->cost(request);
        if (cost < min) {
            min = cost;
            min_cabin = i;
        }
    }
    for (int i = 1; i < first_cost_calculate; i++) {
        double cost = cabin_controllers[i]->cost(request);
        if (cost < min) {
            min = cost;
            min_cabin = i;
        }
    }
    return min_cabin;
}

