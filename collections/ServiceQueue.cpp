//
// Created by jakobolsson on 3/8/23.
//


#include "ServiceQueue.h"

ServiceQueue::ServiceQueue(int floors) {
    this->floors =  floors;
    type = new Direction[floors];
    pending = new bool[floors];
    for (int i = 0; i < floors; i++)
        pending[i] = false;
    preferred_dir = NONE;
}

void ServiceQueue::push(Request request) {
    if (!pending[request.floor]) {
        type[request.floor] = request.direction;
        pending[request.floor] = true;
    }
    else if (type[request.floor] != NONE && request.type == DROPOFF) {
        std::cout << "overwrite" << std::endl;
        type[request.floor] = NONE;
    }
    print();
}

int ServiceQueue::peek() {
    if (isEmpty())
        throw "No elements";
    switch (preferred_dir) {
        case UP:
            for (int i = ceil(position); i < floors; i++)
                if (pending[i] && (type[i] == NONE || type[i] == UP))
                    return i;
            for (int i = floors - 1; i >= ceil(position); i--)
                if (pending[i] && (type[i] == NONE || type[i] == DOWN))
                    return i;
            preferred_dir = DOWN;
            break;
        case DOWN:
            for (int i = floor(position); i >= 0; i--)
                if (pending[i] && (type[i] == NONE || type[i] == DOWN))
                    return i;
            for (int i = 0; i <= floor(position); i++)
                if (pending[i] && (type[i] == NONE || type[i] == UP))
                    return i;
            preferred_dir = UP;
            break;
        case NONE:
            for (int i = 0; i < floors; i++)
                if (pending[i]) {
                    preferred_dir = i < position ? DOWN : UP;
                    return i;
                }
            break;
    }
}

void ServiceQueue::pop() {
    pending[peek()] = false;
    if (isEmpty())
        preferred_dir = NONE;
    print();
}

bool ServiceQueue::isEmpty() {
    for (int i = 0; i < floors; i++)
        if (pending[i])
            return false;
    return true;
}

void ServiceQueue::print() {
    std::cout << "[";
    for (int i = 0; i < floors - 1; i++)
        std::cout << pending[i] << ", ";
    std::cout << pending[floors - 1] << "]" << std::endl;
}

void ServiceQueue::updatePosition(double new_position) {
    this->position = new_position;
}

double ServiceQueue::cost(Request request) {
//    // Saving state
//    double position_bak = position;
//    Direction preferred_dir_bak = preferred_dir;
//    Request requests_bak[floors];
//    bool pending_bak[floors];
//    for (int i = 0; i < floors; i++) {
//        requests_bak[i] = requests[i];
//        pending_bak[i] = pending[i];
//    }
//    // Calculate cost
//    double cost = 0;
//    push(request);
//    if (peek() == request.floor) {
//        cost = fabs(position - request.floor);
//        goto restore;
//    }
//    while (true) {
//        int floor = peek();
//        if (floor == request.floor)
//            break;
//        else
//            cost += fabs(position - floor);
//        pop();
//        position = floor;
//    }
//    // Restore state
//    restore:
//    position = position_bak;
//    preferred_dir = preferred_dir_bak;
//    for (int i = 0; i < floors; i++) {
//        requests[i] = requests_bak[i];
//        pending[i] = pending_bak[i];
//    }
//    return cost;
//    double cost = 0;
//    for (int i = 0; i < floors; i++)
//        if (pending[i])
//            cost++;
//    return cost;
    return 0;
}

