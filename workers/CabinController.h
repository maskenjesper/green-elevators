//
// Created by jakobolsson on 3/10/23.
//

#ifndef GREEN_ELEVATORS_CABINCONTROLLER_H
#define GREEN_ELEVATORS_CABINCONTROLLER_H

#include <csignal>
#include "../collections/ServiceQueue.h"
#include "../utils/enums.h"
#include "../utils/CommandSender.h"

class CabinController {
private:
    pthread_t tid;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int id;
    double position;
    int scale;
    double speed;
    ServiceQueue* stops;
    Direction direction;
private:
    static void* worker(void* args);

public:
    CabinController(int id);
    ~CabinController();
    void addStop(Request request);
    void updatePosition(double position);
    void updateSpeed(double speed);
    void emergencyStop();
    double cost(Request request);
};


#endif //GREEN_ELEVATORS_CABINCONTROLLER_H
