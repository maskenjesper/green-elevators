
#include "ElevatorController.h"


int ElevatorController::cabins;
CabinState *ElevatorController::cabinStates;
pthread_t *ElevatorController::tids;
double ElevatorController::speed;

void ElevatorController::init(int cabinsArg) {
    cabins = cabinsArg;
    getSpeed();
    cabinStates = new CabinState[cabins];
    tids = new pthread_t[cabins];
    for (int i = 0; i < cabins; i++) {
        cabinStates[i].id = int(i+1);
        pthread_create(&tids[i], nullptr, cabinController, &cabinStates[i]);
    }
}

void ElevatorController::quit() {
    for (int i = 0; i < cabins; i++)
        pthread_join(tids[i], nullptr);
}

void *ElevatorController::cabinController(void *args) {
    CabinState* state = (CabinState*) args;
    state->position = 0;
    state->scale = 0;
    state->direction = NONE;
    pthread_mutex_init(&state->lock, nullptr);
    pthread_cond_init(&state->cond, nullptr);
    pthread_mutex_lock(&state->lock);
    while (true) {
        if (!state->stops.isEmpty()) {
            try {
                if (state->position < state->stops.peek() - 0.05) {
                    state->direction = UP;
                    CommandSender::syncHandleMotor(state->id, MotorAction::MotorUp);
                }
                else if (state->position > state->stops.peek() + 0.05) {
                    state->direction = DOWN;
                    CommandSender::syncHandleMotor(state->id, MotorAction::MotorDown);
                }
                else {
                    state->direction = NONE;
                    CommandSender::syncHandleMotor(state->id, MotorAction::MotorStop);
                    CommandSender::syncHandleDoor(state->id, DoorAction::DoorOpen);
                    pthread_mutex_unlock(&state->lock);
                    sleep(3);
                    pthread_mutex_lock(&state->lock);
                    CommandSender::syncHandleDoor(state->id, DoorAction::DoorClose);
                    state->stops.pop();
                }
            }
            catch (const char* e) {
                continue;
            }
        }
        pthread_cond_wait(&state->cond, &state->lock);
    }
    pthread_mutex_unlock(&state->lock);
}

void ElevatorController::addStop(int cabin, Request request) {
    pthread_mutex_lock(&cabinStates[cabin - 1].lock);
    cabinStates[cabin - 1].stops.push(request, cabinStates[cabin - 1].position, cabinStates[cabin - 1].direction);
    pthread_cond_broadcast(&cabinStates[cabin - 1].cond);
    pthread_mutex_unlock(&cabinStates[cabin - 1].lock);
}

void ElevatorController::updatePosition(int cabin, double position) {
    pthread_mutex_lock(&cabinStates[cabin - 1].lock);
    cabinStates[cabin - 1].position = position;
    if (cabinStates[cabin - 1].scale != (int) round(position)) {
        cabinStates[cabin - 1].scale = (int) round(position);
        CommandSender::syncHandleScale(cabin, (int) round(position));
    }
    pthread_cond_broadcast(&cabinStates[cabin - 1].cond);
    pthread_mutex_unlock(&cabinStates[cabin - 1].lock);
}

void ElevatorController::updateSpeed(double speedArg) {
    speed = speedArg;
}

void ElevatorController::emergencyStop(int cabin) {
    pthread_mutex_lock(&cabinStates[cabin - 1].lock);
    cabinStates[cabin - 1].stops.clear();
    CommandSender::syncHandleMotor(cabin, MotorAction::MotorStop);
    pthread_mutex_unlock(&cabinStates[cabin - 1].lock);

}

int ElevatorController::lowestCost(Request request) {
    double min = std::numeric_limits<int>::max();
    int min_cabin;
    for (int i = 0; i < cabins; i++) {
        pthread_mutex_lock(&cabinStates[i].lock);
        double cost = cabinStates[i].stops.cost(request, cabinStates[i].position, cabinStates[i].direction);
        pthread_mutex_unlock(&cabinStates[i].lock);
        if (cost < min) {
            min = cost;
            min_cabin = i + 1;
        }
    }
    return min_cabin;
}

