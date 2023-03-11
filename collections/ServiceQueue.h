//
// Created by jakobolsson on 3/8/23.
//

#ifndef GREEN_ELEVATORS_SERVICEQUEUE_H
#define GREEN_ELEVATORS_SERVICEQUEUE_BAK_H


#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "../structures/Request.h"

class ServiceQueue {
private:
    Direction* type;
    bool* pending;
    int floors;
    Direction preferred_dir;
    double position;
private:
    void print();

public:
    explicit ServiceQueue(int floors);
    double cost(Request request);
    void push(Request request);
    int peek();
    void pop();
    void updatePosition(double new_position);
    bool isEmpty();
};


#endif //GREEN_ELEVATORS_SERVICEQUEUE_H
