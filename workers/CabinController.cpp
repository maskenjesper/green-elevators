//
// Created by jakobolsson on 3/10/23.
//


#include "CabinController.h"


CabinController::CabinController(int id, int floors) {
    this->id = id;
    pthread_mutex_init(&lock, nullptr);
    pthread_cond_init(&cond, nullptr);
    position = 0;
    scale = 0;
    direction = NONE;
    stops = new ServiceQueue(floors);
    pthread_create(&tid, nullptr, worker, this);
}

CabinController::~CabinController() {
    pthread_join(tid, nullptr);
    delete stops;
}

void* CabinController::worker(void* args) {
    auto self = (CabinController*) args;
    pthread_mutex_lock(&self->lock);
    while (true) {
        if (!self->stops->isEmpty()) {
            if (self->stops->peek(self->position, self->direction) == -1) {
                self->direction = self->direction == UP ? DOWN : UP;
            }
            else if (self->position < self->stops->peek(self->position, self->direction) - 0.05) {
                self->direction = UP;
                CommandSender::syncHandleMotor(self->id, MotorAction::MotorUp);
            }
            else if (self->position > self->stops->peek(self->position, self->direction) + 0.05) {
                self->direction = DOWN;
                CommandSender::syncHandleMotor(self->id, MotorAction::MotorDown);
            }
            else {
                if (!self->stops->isEmpty()) {
                    std::cout << self->id << " pop:\t";
                    self->stops->pop(self->position, self->direction);
                }
                CommandSender::syncHandleMotor(self->id, MotorAction::MotorStop);
                CommandSender::syncHandleDoor(self->id, DoorAction::DoorOpen);
                pthread_mutex_unlock(&self->lock);
                sleep(3);
                pthread_mutex_lock(&self->lock);
                CommandSender::syncHandleDoor(self->id, DoorAction::DoorClose);
            }
        }
        else
            self->direction = NONE;
        pthread_cond_wait(&self->cond, &self->lock);
    }
    pthread_mutex_unlock(&self->lock);
}

void CabinController::addStop(Request request) {
    pthread_mutex_lock(&lock);
    std::cout << this->id << " push:\t";
    stops->push(request);
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
    CommandSender::syncHandleMotor(id, MotorAction::MotorStop);
}

double CabinController::cost(Request request) {
    pthread_mutex_lock(&lock);
    double cost = stops->cost(request, position, direction);
    pthread_mutex_unlock(&lock);
    return cost;
}

