//
// Created by jakobolsson on 3/10/23.
//


#include "CabinController.h"


CabinController::CabinController(int id) {
    this->id = id;
    pthread_create(&tid, nullptr, worker, this);
}

CabinController::~CabinController() {
    pthread_join(tid, nullptr);
}

void* CabinController::worker(void* args) {
    CabinController* self = (CabinController*) args;

    self->position = 0;
    self->scale = 0;
    self->direction = NONE;
    pthread_mutex_init(&self->lock, nullptr);
    pthread_cond_init(&self->cond, nullptr);
    pthread_mutex_lock(&self->lock);
    while (true) {
        if (!self->stops.isEmpty()) {
            try {
                if (self->position < self->stops.peek() - 0.05) {
                    self->direction = UP;
                    CommandSender::syncHandleMotor(self->id, MotorAction::MotorUp);
                }
                else if (self->position > self->stops.peek() + 0.05) {
                    self->direction = DOWN;
                    CommandSender::syncHandleMotor(self->id, MotorAction::MotorDown);
                }
                else {
                    self->direction = NONE;
                    CommandSender::syncHandleMotor(self->id, MotorAction::MotorStop);
//                    CommandSender::syncHandleDoor(self->id, DoorAction::DoorOpen);
//                    pthread_mutex_unlock(&self->lock);
//                    sleep(3);
//                    pthread_mutex_lock(&self->lock);
//                    CommandSender::syncHandleDoor(self->id, DoorAction::DoorClose);
                    self->stops.pop();
                }
            }
            catch (const char* e) {
                continue;
            }
        }
        pthread_cond_wait(&self->cond, &self->lock);
    }
    pthread_mutex_unlock(&self->lock);
}

void CabinController::addStop(Request request) {
    pthread_mutex_lock(&lock);
    stops.push(request, position, direction);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);
}

void CabinController::updatePosition(double position) {
    pthread_mutex_lock(&lock);
    this->position = position;
    if (scale != (int) round(position)) {
        scale = (int) round(position);
        CommandSender::syncHandleScale(id, (int) round(position));
    }
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);
}

void CabinController::updateSpeed(double speed) {
    this->speed = speed;
}

void CabinController::emergencyStop() {
    pthread_mutex_lock(&lock);
    stops.clear();
    CommandSender::syncHandleMotor(id, MotorAction::MotorStop);
    pthread_mutex_unlock(&lock);
}

double CabinController::cost(Request request) {
    pthread_mutex_lock(&lock);
    double cost = stops.cost(request, position, direction);
    pthread_mutex_unlock(&lock);
    return cost;
}

