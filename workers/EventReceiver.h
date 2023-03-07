#ifndef GREEN_ELEVATORS_EVENTRECEIVER_H
#define GREEN_ELEVATORS_EVENTRECEIVER_H

#include <pthread.h>
#include <iostream>

#include "../utils/hardwareAPI.h"
#include "../structures/ActionQueue.h"
#include "ElevatorController.h"
#include "../structures/Action.h"

class EventReceiver {
private:
    static pthread_t tid;
    static ActionQueue *actionQueue;
private:
    static void *worker(void *);
    EventReceiver();

public:
    static void init(ActionQueue *actionQueue);
    static void quit();
};

#endif //GREEN_ELEVATORS_EVENTRECEIVER_H
