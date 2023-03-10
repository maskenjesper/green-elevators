//
// Created by jakobolsson on 3/10/23.
//

#ifndef GREEN_ELEVATORS_COMMANDSENDER_H
#define GREEN_ELEVATORS_COMMANDSENDER_H

#include <pthread.h>
#include "hardwareAPI.h"

class CommandSender {
private:
    static pthread_mutex_t cmd_lock;

public:
    static void init();
    static void syncHandleDoor(int cabin, DoorAction action);
    static void syncHandleMotor(int cabin, MotorAction action);
    static void syncHandleScale(int cabin, int floor);
    static void syncWhereIs(int cabin);
    static void syncGetSpeed();
};


#endif //GREEN_ELEVATORS_COMMANDSENDER_H
