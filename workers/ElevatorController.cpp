#include <cmath>
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
        if (!state->stops.empty()) {
            if (state->position < state->stops.front() - 0.05) {
                state->direction = UP;
                handleMotor(state->id, MotorAction::MotorUp);
            }
            else if (state->position > state->stops.front() + 0.05) {
                state->direction = DOWN;
                handleMotor(state->id, MotorAction::MotorDown);
            }
            else {
                state->direction = NONE;
                handleMotor(state->id, MotorAction::MotorStop);
                state->stops.pop();
                handleDoor(state->id, DoorAction::DoorOpen);
                std::cout << speed;
                pthread_mutex_unlock(&state->lock);
                sleep(3);
                pthread_mutex_lock(&state->lock);
                handleDoor(state->id, DoorAction::DoorClose);
            }
        }
        pthread_cond_wait(&state->cond, &state->lock);
    }
    pthread_mutex_unlock(&state->lock);
}

void ElevatorController::addStop(int cabin, int level) {
    // TODO: add stop at right place according to wanted scheduling behaviour.
    pthread_mutex_lock(&cabinStates[cabin - 1].lock);
    cabinStates[cabin - 1].stops.push(level);
    std::cout << "stop added to cabin " << cabin << std::endl;
    pthread_cond_broadcast(&cabinStates[cabin - 1].cond);
    pthread_mutex_unlock(&cabinStates[cabin - 1].lock);
}

void ElevatorController::updatePosition(int cabin, double position) {
    pthread_mutex_lock(&cabinStates[cabin - 1].lock);
    cabinStates[cabin - 1].position = position;
    if (cabinStates[cabin - 1].scale != (int) round(position)) {
        cabinStates[cabin - 1].scale = (int) round(position);
        handleScale(cabin, (int) round(position));
    }
    pthread_cond_broadcast(&cabinStates[cabin - 1].cond);
    pthread_mutex_unlock(&cabinStates[cabin - 1].lock);
}

void ElevatorController::updateSpeed(double speedArg) {
    speed = speedArg;
}

