#ifndef GREEN_ELEVATORS_ELEVATORCONTROLLER_H
#define GREEN_ELEVATORS_ELEVATORCONTROLLER_H

#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <pthread.h>
#include <iostream>
#include <queue>
#include <cmath>
#include <limits>

#include "../structures/Request.h"
#include "CabinController.h"

class ElevatorController {
private:
    static int cabins;
    static CabinController* cabin_controllers[];
private:
    static void* cabinController(void*);
    ElevatorController();

public:
    static void init(int cabins);
    static void quit();
    static void addStop(int cabin, Request request);
    static void updatePosition(int cabin, double position);
    static void updateSpeed(double speed);
    static void emergencyStop(int cabin);
    static int lowestCost(Request request);
};

#endif //GREEN_ELEVATORS_ELEVATORCONTROLLER_H
