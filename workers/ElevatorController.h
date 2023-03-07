#ifndef GREEN_ELEVATORS_ELEVATORCONTROLLER_H
#define GREEN_ELEVATORS_ELEVATORCONTROLLER_H

#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <pthread.h>
#include <iostream>

#include "../utils/hardwareAPI.h"
#include "../structures/ActionQueue.h"

struct CabinState {
    double position;
    int scale;
    CabinDirection direction;
};

class ElevatorController {
private:
    static pthread_t *controllerTid;
    static pthread_t schedulerTid;
    static int cabins;
    static CabinState *cabinStates;
    static ActionQueue *actionQueue;
    static std::vector<int> *cabinPaths;
    static double speed;
private:
    static void *scheduler(void *);
    static void *cabinController(void *);
    ElevatorController();

public:
    static void init(ActionQueue *actionQueue, int cabins);
    static void quit();
    static void updatePosition(int cabin, double position);
    static void updateSpeed(double speedArg);
};

#endif //GREEN_ELEVATORS_ELEVATORCONTROLLER_H
