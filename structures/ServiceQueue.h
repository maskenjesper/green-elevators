//
// Created by jakobolsson on 3/8/23.
//

#ifndef GREEN_ELEVATORS_SERVICEQUEUE_H
#define GREEN_ELEVATORS_SERVICEQUEUE_H


#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "Action.h"

struct Node {
    int value;
    Node* next;
    Node* prev;

    Node(int value, Node* next, Node* prev) {
        this->value = value;
        this->next = next;
        this->prev = prev;
    }
};

class ServiceQueue {
private:
    Node* head; // Points at the first floor in queue
    Node* turn; // Points at the first floor on return in queue
    Node* tail; // Points at the last floor in queue
private:
    void print();
    void pushOrdered(Node* from, Direction direction, int level);
    bool contains(int value);
    void remove(int value);

public:
    ServiceQueue();
    double cost(Action action, double current_pos, Direction current_dir);
    void push(Action action, double current_pos, Direction current_dir);
    int peek();
    void pop();
    bool isEmpty();
    void clear();
};


#endif //GREEN_ELEVATORS_SERVICEQUEUE_H
