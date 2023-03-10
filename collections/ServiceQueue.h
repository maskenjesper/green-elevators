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
    Request* requests;
    bool* pending;
    int floors;
private:
    void print();

public:
    ServiceQueue(int floors);
    double cost(Request request, double current_pos, Direction current_dir);
    void push(Request request);
    int peek(double current_pos, Direction current_dir);
    void pop(double current_pos, Direction current_dir);
    bool isEmpty();
};


#endif //GREEN_ELEVATORS_SERVICEQUEUE_H
