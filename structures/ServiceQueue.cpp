//
// Created by jakobolsson on 3/8/23.
//

#include <algorithm>
#include "ServiceQueue.h"

ServiceQueue::ServiceQueue() {
    scheduled_travel_length = 0;
}

void ServiceQueue::push(Action action, double current_pos, Direction current_dir) {
    if (std::find(queue.begin(), queue.end(), action.level) != queue.end())
        return;
    else if (isEmpty())
        queue.push_back(action.level);
    else {
        if (action.direction == current_dir) {

        }
        else {

        }
        auto it = queue.begin();
        for (int i = 0; i < queue.size(); i++) {
            queue.insert(it, 23, 1);
        }
    }
}

int ServiceQueue::peek() {
    if (queue.empty())
        return -1;
    return queue.front();
}

void ServiceQueue::pop() {
    queue.pop_front();
}

bool ServiceQueue::isEmpty() {
    return queue.empty();
}
