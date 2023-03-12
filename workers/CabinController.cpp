#include "CabinController.h"

#include <cmath>

CabinController::CabinController(int id, int floors) {
    this->id = id;
    pthread_mutex_init(&lock, nullptr);
    pthread_cond_init(&cond, nullptr);
    position = 0;
    scale = 0;
    serviceQueue = new ServiceQueue(floors);
    pthread_create(&tid, nullptr, worker, this);
}

CabinController::~CabinController() {
    pthread_join(tid, nullptr);
    delete serviceQueue;
}

void* CabinController::worker(void* args) {
    auto self = (CabinController*) args;
    pthread_mutex_lock(&self->lock);
    while (true) {
        if (!self->serviceQueue->isEmpty()) {
            if (self->position < self->serviceQueue->peek() - 0.06)
                CommandSender::syncHandleMotor(self->id, MotorAction::MotorUp);
            else if (self->position > self->serviceQueue->peek() + 0.06)
                CommandSender::syncHandleMotor(self->id, MotorAction::MotorDown);
            else {
                if (!self->serviceQueue->isEmpty()) {
                    std::cout << self->id << " pop:\t";
                    self->serviceQueue->pop();
                }
                CommandSender::syncHandleMotor(self->id, MotorAction::MotorStop);
                CommandSender::syncHandleDoor(self->id, DoorAction::DoorOpen);
                pthread_mutex_unlock(&self->lock);

                double sleepAmount = self->speed*1000;
                //std:: cout<<"SPEED:"<<sleepAmount<<std::endl;
                double doorWaitingTime= self->calculateTimeForDoors(sleepAmount);
                //std::cout<<"CALCULATED SPEED;"<<doorWaitingTime << std::endl;

                usleep(doorWaitingTime);
                pthread_mutex_lock(&self->lock);
                CommandSender::syncHandleDoor(self->id, DoorAction::DoorClose);
            }
        }
        pthread_cond_wait(&self->cond, &self->lock);
    }
    pthread_mutex_unlock(&self->lock);
}


double CabinController::calculateTimeForDoors(double floorsPerSecond) {
    double doorWaitingTime = (274.988 - (582.958 * floorsPerSecond)) + ((77.5593)*(floorsPerSecond*floorsPerSecond)) - ((269.26)* (cos(floorsPerSecond))) +  ((527.324) *(floorsPerSecond * cos(floorsPerSecond)));
    double doorWaitingTimeConvertedToMicroSec = doorWaitingTime * 1000000;
    return doorWaitingTimeConvertedToMicroSec;
}

void CabinController::addStop(Request request) {
    pthread_mutex_lock(&lock);
    std::cout << this->id << " push:\t";
    serviceQueue->push(request);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);
}

void CabinController::updatePosition(double new_position) {
    pthread_mutex_lock(&lock);
    this->position = new_position;
    if (scale != (int) round(new_position)) {
        scale = (int) round(new_position);
        CommandSender::syncHandleScale(id, (int) round(new_position));
    }
    serviceQueue->updatePosition(new_position);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);
}

void CabinController::updateSpeed(double new_speed) {
    this->speed = new_speed;
}

void CabinController::emergencyStop() const {
    CommandSender::syncHandleMotor(id, MotorAction::MotorStop);
}

double CabinController::cost(Request request) {
    pthread_mutex_lock(&lock);
    double cost = serviceQueue->cost(request);
    pthread_mutex_unlock(&lock);
    std::cout << "The cost for cabin " << id << " was " << cost << std::endl;
    return cost;
}



