#ifndef GREEN_ELEVATORS_SERVICEQUEUE_H
#define GREEN_ELEVATORS_SERVICEQUEUE_BAK_H


#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "../structures/Request.h"

struct Backup {
    Direction* type;
    bool* pending;
    int floors;
    Direction preferred_dir;
    double position;

    Backup(const Direction* type, const bool* pending, int floors, Direction preferred_dir, double position) {
        this->type = new Direction[floors];
        this->pending = new bool[floors];
        for (int i = 0; i < floors; i++) {
            this->type[i] = type[i];
            this->pending[i] = pending[i];
        }
        this->floors = floors;
        this->preferred_dir = preferred_dir;
        this->position = position;
    }

    ~Backup() {
        delete type;
        delete pending;
    }
};

class ServiceQueue {
private:
    Direction* type; // Describes the type of each request per floor
    bool* pending; // Describes which floors have a pending request
    int floors;
    Direction preferred_dir; // The cabins current preferred direction to serve requests in.
                             // Inspired from the LOOK algorithm.
    double position;
private:
    void restore(Backup* backup);

public:
    void print();
    explicit ServiceQueue(int floors);
    double cost(Request request);
    void push(Request request);
    int peek();
    void pop();
    void updatePosition(double new_position);
    bool isEmpty();
};


#endif //GREEN_ELEVATORS_SERVICEQUEUE_H
