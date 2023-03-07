//
// Created by jakobolsson on 3/3/23.
//

#include "ActionQueue.h"

ActionQueue::ActionQueue() {
    pthread_mutex_init(&queue_lock, nullptr);
    pthread_cond_init(&queue_cond, nullptr);
}

void ActionQueue::add(Action *action) {
    pthread_mutex_lock(&queue_lock);
    queue.push_back(action);
    pthread_cond_broadcast(&queue_cond);
    pthread_mutex_unlock(&queue_lock);
}

Action *ActionQueue::remove() {
    if (queue.empty())
        throw std::out_of_range("No elements in queue");
    Action *action = queue[0];
    pthread_mutex_lock(&queue_lock);
    queue.pop_back();
    pthread_cond_broadcast(&queue_cond);
    pthread_mutex_unlock(&queue_lock);
    return action;
}

unsigned long ActionQueue::size() {
    return queue.size();
}

void ActionQueue::wait() {
    pthread_mutex_lock(&queue_lock);
    pthread_cond_wait(&queue_cond, &queue_lock);
    pthread_mutex_unlock(&queue_lock);
}
