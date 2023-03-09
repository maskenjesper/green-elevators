
#include "ElevatorController.h"


int ElevatorController::cabins;
CabinState *ElevatorController::cabinStates;
pthread_t *ElevatorController::tids;
double ElevatorController::speed;
pthread_mutex_t ElevatorController::cmd_lock;

void ElevatorController::init(int cabinsArg) {
    cabins = cabinsArg;
    getSpeed();
    cabinStates = new CabinState[cabins];
    pthread_mutex_init(&cmd_lock, nullptr);
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
                    pthread_mutex_lock(&cmd_lock);
                    handleMotor(state->id, MotorAction::MotorUp);
                    pthread_mutex_unlock(&cmd_lock);
                }
                else if (state->position > state->stops.peek() + 0.05) {
                    state->direction = DOWN;
                    pthread_mutex_lock(&cmd_lock);
                    handleMotor(state->id, MotorAction::MotorDown);
                    pthread_mutex_unlock(&cmd_lock);
                }
                else {
                    state->direction = NONE;
                    pthread_mutex_lock(&cmd_lock);
                    handleMotor(state->id, MotorAction::MotorStop);
                    handleDoor(state->id, DoorAction::DoorOpen);
                    pthread_mutex_unlock(&cmd_lock);
                    pthread_mutex_unlock(&state->lock);
                    sleep(3);
                    pthread_mutex_lock(&state->lock);
                    pthread_mutex_lock(&cmd_lock);
                    handleDoor(state->id, DoorAction::DoorClose);
                    pthread_mutex_unlock(&cmd_lock);
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

void ElevatorController::addStop(int cabin, Action action) {
    // TODO: add stop at right place according to wanted scheduling behaviour.
    pthread_mutex_lock(&cabinStates[cabin - 1].lock);
    cabinStates[cabin - 1].stops.push(action, cabinStates[cabin - 1].position, cabinStates[cabin - 1].direction);
    pthread_cond_broadcast(&cabinStates[cabin - 1].cond);
    pthread_mutex_unlock(&cabinStates[cabin - 1].lock);
}

void ElevatorController::updatePosition(int cabin, double position) {
    pthread_mutex_lock(&cabinStates[cabin - 1].lock);
    cabinStates[cabin - 1].position = position;
    if (cabinStates[cabin - 1].scale != (int) round(position)) {
        cabinStates[cabin - 1].scale = (int) round(position);
        pthread_mutex_lock(&cmd_lock);
        handleScale(cabin, (int) round(position));
        pthread_mutex_unlock(&cmd_lock);
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
    pthread_mutex_lock(&cmd_lock);
    handleMotor(cabin, MotorAction::MotorStop);
    pthread_mutex_unlock(&cmd_lock);
    pthread_mutex_unlock(&cabinStates[cabin - 1].lock);

}

int ElevatorController::lowestCost(Action action) {
    double min = std::numeric_limits<int>::max();
    int min_cabin;
    for (int i = 0; i < cabins; i++) {
        pthread_mutex_lock(&cabinStates[i].lock);
        double cost = cabinStates[i].stops.cost(action, cabinStates[i].position, cabinStates[i].direction);
        pthread_mutex_unlock(&cabinStates[i].lock);
        if (cost < min) {
            min = cost;
            min_cabin = i + 1;
        }
    }
    return min_cabin;
}

