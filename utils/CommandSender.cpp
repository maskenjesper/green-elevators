//
// Created by jakobolsson on 3/10/23.
//

#include "CommandSender.h"

pthread_mutex_t CommandSender::cmd_lock;

void CommandSender::init() {
    pthread_mutex_init(&cmd_lock, nullptr);
}

void CommandSender::syncHandleDoor(int cabin, DoorAction action) {
    pthread_mutex_lock(&cmd_lock);
    handleDoor(cabin, action);
    pthread_mutex_unlock(&cmd_lock);
}

void CommandSender::syncHandleMotor(int cabin, MotorAction action) {
    pthread_mutex_lock(&cmd_lock);
    handleMotor(cabin, action);
    pthread_mutex_unlock(&cmd_lock);
}

void CommandSender::syncHandleScale(int cabin, int floor) {
    pthread_mutex_lock(&cmd_lock);
    handleScale(cabin, floor);
    pthread_mutex_unlock(&cmd_lock);
}

void CommandSender::syncWhereIs(int cabin) {
    pthread_mutex_lock(&cmd_lock);
    whereIs(cabin);
    pthread_mutex_unlock(&cmd_lock);
}

void CommandSender::syncGetSpeed() {
    pthread_mutex_lock(&cmd_lock);
    getSpeed();
    pthread_mutex_unlock(&cmd_lock);
}

