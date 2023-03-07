#ifndef GREEN_ELEVATORS_COMMANDSENDER_H
#define GREEN_ELEVATORS_COMMANDSENDER_H

#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <pthread.h>
#include <iostream>

#include "../utils/hardwareAPI.h"
#include "../structures/ActionQueue.h"

class CommandSender {
private:
    static void *worker(void *);
    CommandSender();

public:
    static ActionQueue *actionQueue;
    static pthread_t init(ActionQueue *actionQueue);
};

#endif //GREEN_ELEVATORS_COMMANDSENDER_H
