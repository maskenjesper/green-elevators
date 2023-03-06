#ifndef GREEN_ELEVATORS_COMMANDRECEIVER_H
#define GREEN_ELEVATORS_COMMANDRECEIVER_H

#include <pthread.h>
#include <iostream>

#include "../utils/hardwareAPI.h"
#include "../structures/ActionQueue.h"

class CommandReceiver {
private:
    static ActionQueue actionQueue;
    static void *worker(void *);

public:
    static pthread_t init(ActionQueue actionQueue);
};

#endif //GREEN_ELEVATORS_COMMANDRECEIVER_H
