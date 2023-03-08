//
// Created by jakobolsson on 3/8/23.
//

#ifndef GREEN_ELEVATORS_SERVICEQUEUE_H
#define GREEN_ELEVATORS_SERVICEQUEUE_H


#include <list>
#include "Action.h"

class ServiceQueue {
private:
    std::list<int> queue;
    double scheduled_travel_length;

public:
    ServiceQueue();
    void push(Action action, double current_pos, Direction current_dir);
    int peek();
    void pop();
    bool isEmpty();
};


#endif //GREEN_ELEVATORS_SERVICEQUEUE_H
