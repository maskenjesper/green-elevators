//
// Created by jakobolsson on 3/3/23.
//

#include "ActionQueue.h"

ActionQueue::ActionQueue() {
    pthread_mutex_init(&queue_lock, NULL);
}

void ActionQueue::add(Action action) {
    pthread_mutex_lock(&queue_lock);
    queue.push_back(action);
    pthread_mutex_unlock(&queue_lock);
}

void ActionQueue::remove() {
    pthread_mutex_lock(&queue_lock);
    queue.pop_back();
    pthread_mutex_unlock(&queue_lock);
}

Action ActionQueue::peek() {
    return queue[0];
}
