#include "ElevatorController.h"

void ElevatorController::init(int cabinsArg) {
    cabins = cabinsArg;
    getSpeed();
    cabinStates = reinterpret_cast<CabinState **>(new CabinState[cabins]);
    tids = new pthread_t[cabins];
    for (int i = 0; i < cabins; i++) {
        cabinStates[i]->id = int(i+1);
        pthread_create(&tids[i], nullptr, cabinController, cabinStates[i]);
    }
}

void ElevatorController::quit() {
    for (int i = 0; i < cabins; i++)
        pthread_join(tids[i], nullptr);
}

void *ElevatorController::cabinController(void *args) {
    CabinState state = *(CabinState*) args;
    state.position = 0;
    state.scale = 0;
    state.direction = NONE;
    pthread_mutex_init(&state.lock, nullptr);
    pthread_cond_init(&state.cond, nullptr);
    pthread_mutex_lock(&state.lock);
    while (true) {
        if (!state.stops.empty()) {
            if (state.position < state.stops.top() - 0.05) {
                state.direction = UP;
                handleMotor(state.id, MotorAction::MotorUp);
            }
            else if (state.position > state.stops.top() + 0.05) {
                state.direction = DOWN;
                handleMotor(state.id, MotorAction::MotorDown);
            }
            else {
                state.direction = NONE;
                handleMotor(state.id, MotorAction::MotorStop);
                state.stops.pop();
                handleDoor(state.id, DoorAction::DoorOpen);
                std::cout << speed;
                pthread_mutex_unlock(&state.lock);
                sleep(3);
                pthread_mutex_lock(&state.lock);
                handleDoor(state.id, DoorAction::DoorClose);
            }
        }
        pthread_cond_wait(&state.cond, &state.lock);
    }
    pthread_mutex_unlock(&state.lock);
}

void ElevatorController::addStop(int cabin, int level) {

}

void ElevatorController::updatePosition(int cabin, double position) {
    cabinStates[cabin - 1]->position = position;
    if (cabinStates[cabin - 1]->scale != (int) position) {
        cabinStates[cabin - 1]->scale = (int) position;
        handleScale(cabin, (int) position);
    }
}

void ElevatorController::updateSpeed(double speedArg) {
    speed = speedArg;
}

