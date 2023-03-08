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

#include "../utils/hardwareAPI.h"
#include "../utils/enums.h"
#include "../structures/ServiceQueue.h"
#include "../structures/Action.h"

struct CabinState {
    int id;
    double position;
    int scale;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    ServiceQueue stops;
    Direction direction;
};

class ElevatorController {
private:
    static pthread_t* tids;
    static int cabins;
    static double speed;
    static CabinState* cabinStates;
private:
    static void* cabinController(void*);
    ElevatorController();

public:
    static void init(int cabins);
    static void quit();
    static void addStop(int cabin, Action action);
    static void updatePosition(int cabin, double position);
    static void updateSpeed(double speedArg);
};

#endif //GREEN_ELEVATORS_ELEVATORCONTROLLER_H
