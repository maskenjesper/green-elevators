#include "ElevatorController.h"

pthread_t *ElevatorController::controllerTid;
pthread_t ElevatorController::schedulerTid;
int ElevatorController::cabins;
CabinState *ElevatorController::cabinStates;
ActionQueue *ElevatorController::actionQueue;
std::vector<int> *ElevatorController::cabinPaths;
double ElevatorController::speed;

void ElevatorController::init(ActionQueue *actionQueueArg, int cabinsArg) {
    actionQueue = actionQueueArg;
    cabins = cabinsArg;
    cabinStates = new CabinState[cabins];
    controllerTid = new pthread_t[cabins];
    cabinPaths = new std::vector<int>[cabins];
    getSpeed();
    for (int i = 0; i < cabins; i++) {
        cabinStates[i].position = 0;
        cabinStates[i].scale = 0;
        cabinStates[i].direction = NONE;
        whereIs(i + 1);
    }
    pthread_create(&schedulerTid, nullptr, scheduler, nullptr);
    for (int i = 0; i < cabins; i++) {
        int *id = new int(i);
        pthread_create(&controllerTid[i], nullptr, cabinController, id);
    }
}

void ElevatorController::quit() {
    pthread_join(schedulerTid, nullptr);
    for (int i = 0; i < cabins; i++)
        pthread_join(controllerTid[i], nullptr);
}

void *ElevatorController::scheduler(void *) {
    while (true) {
        try {
            Action *action = actionQueue->remove();
            std::cout << "event sender: " << actionQueue->size();
            for (int i = 0; i < 5; i++)
                std::cout << " " << cabinStates[i].position;
            std::cout << " " << action->getElevator() << std::endl;

            switch (action->getType()) {
                case PICKUP:
                    cabinPaths[0].push_back(action->getFloor());
                    break;
                case DROPOFF:
                    cabinPaths[action->getElevator() - 1].push_back(action->getFloor());
                    break;
            }
        }
        catch (std::out_of_range e) {
            std::cout << "empty" << std::endl;
        }
        actionQueue->wait();
    }
}

void *ElevatorController::cabinController(void *args) {
    int id = *(int *) args;
    while (true) {
        if (!cabinPaths[id].empty()) {
            if (cabinStates[id].position < cabinPaths[id][0] - 0.05) {
                cabinStates[id].direction = UP;
                handleMotor(id + 1, MotorAction::MotorUp);
            }
            else if (cabinStates[id].position > cabinPaths[id][0] + 0.05) {
                cabinStates[id].direction = DOWN;
                handleMotor(id + 1, MotorAction::MotorDown);
            }
            else {
                cabinStates[id].direction = NONE;
                handleMotor(id + 1, MotorAction::MotorStop);
                cabinPaths[id].pop_back();
                handleDoor(id + 1, DoorAction::DoorOpen);
                std::cout << speed;
                sleep(3);
                handleDoor(id + 1, DoorAction::DoorClose);
            }
        }
    }
}

void ElevatorController::updatePosition(int cabin, double position) {
    cabinStates[cabin - 1].position = position;
    if (cabinStates[cabin - 1].scale != (int) position) {
        cabinStates[cabin - 1].scale = (int) position;
        handleScale(cabin, (int) position);
    }
}

void ElevatorController::updateSpeed(double speedArg) {
    speed = speedArg;
}
