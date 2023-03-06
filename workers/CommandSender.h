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
    static ActionQueue actionQueue;
    static void *worker(void *);

public:
    static pthread_t init(ActionQueue actionQueue);
};

#endif //GREEN_ELEVATORS_COMMANDSENDER_H
