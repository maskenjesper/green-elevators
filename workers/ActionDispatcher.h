//
// Created by jakobolsson on 3/7/23.
//

#ifndef GREEN_ELEVATORS_ACTIONDISPATCHER_H
#define GREEN_ELEVATORS_ACTIONDISPATCHER_H


#include <pthread.h>
#include <queue>
#include "../structures/Action.h"
#include "ElevatorController.h"

class ActionDispatcher {
private:
    static pthread_t tid;
    static std::queue<Action> actions;
    static pthread_mutex_t lock;
    static pthread_cond_t cond;

private:
    static void* worker(void*);
    ActionDispatcher();

public:
    static void init();
    static void quit();
    static void addAction(const Action* action);
};


#endif //GREEN_ELEVATORS_ACTIONDISPATCHER_H
