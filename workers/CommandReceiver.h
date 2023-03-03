#ifndef GREEN_ELEVATORS_COMMANDRECEIVER_H
#define GREEN_ELEVATORS_COMMANDRECEIVER_H

#include <pthread.h>
#include <iostream>

#include "../utils/hardwareAPI.h"

class CommandReceiver {
private:
    static void *worker(void *);

public:
    static pthread_t init();
};

#endif //GREEN_ELEVATORS_COMMANDRECEIVER_H
