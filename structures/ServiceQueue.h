//
// Created by jakobolsson on 3/8/23.
//

#ifndef GREEN_ELEVATORS_SERVICEQUEUE_H
#define GREEN_ELEVATORS_SERVICEQUEUE_H


#include <list>
#include <vector>
#include "Action.h"

struct Node {
    int value;
    Node* next;

    Node(int value, Node* next) {
        this->value = value;
        this->next = next;
    }
};

class ServiceQueue {
private:
    Node* head;

public:
    ServiceQueue();
    void push(Action action, double current_pos, Direction current_dir);
    int peek();
    void pop();
    bool isEmpty();
};


#endif //GREEN_ELEVATORS_SERVICEQUEUE_H
