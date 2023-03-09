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
    static pthread_mutex_t cmd_lock;
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
    static void emergencyStop(int cabin);
    static int lowestCost(Action action);
};

#endif //GREEN_ELEVATORS_ELEVATORCONTROLLER_H
