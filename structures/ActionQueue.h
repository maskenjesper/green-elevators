//
// Created by jakobolsson on 3/3/23.
//

#ifndef GREEN_ELEVATORS_ACTIONQUEUE_H
#define GREEN_ELEVATORS_ACTIONQUEUE_H

#include <vector>
#include <pthread.h>
#include <stdexcept>

#include "Action.h"

class ActionQueue {
private:
    std::vector<Action*> queue;
    pthread_mutex_t queue_lock;
    pthread_cond_t queue_cond;

public:
    ActionQueue();
    void add(Action *action);
    Action *remove();
    unsigned long size();
    void wait();
};


#endif //GREEN_ELEVATORS_ACTIONQUEUE_H
