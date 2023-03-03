//
// Created by jakobolsson on 3/3/23.
//

#ifndef GREEN_ELEVATORS_ACTIONQUEUE_H
#define GREEN_ELEVATORS_ACTIONQUEUE_H

#include <vector>
#include <pthread.h>

#include "Action.h"

class ActionQueue {
    private:
        std::vector<Action> queue;
        pthread_mutex_t queue_lock;

    public:
        ActionQueue();
        void add(Action action);
        void remove();
        Action peek();
};


#endif //GREEN_ELEVATORS_ACTIONQUEUE_H
