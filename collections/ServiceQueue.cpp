//
// Created by jakobolsson on 3/8/23.
//


#include "ServiceQueue.h"

ServiceQueue::ServiceQueue(int floors) {
    this->floors =  floors;
    requests = new Request[floors];
    pending = new bool[floors];
    for (int i = 0; i < floors; i++)
        pending[i] = false;
    preferred_dir = NONE;
}

void ServiceQueue::push(Request request) {
    if (isEmpty()) {
        preferred_dir = request.direction;
    }
    if (!pending[request.floor]) {
        requests[request.floor] = request;
        pending[request.floor] = true;
    }
    else if (requests[request.floor].type != DROPOFF && request.type == DROPOFF) {
        std::cout << "overwrite" << std::endl;
        requests[request.floor] = request;
    }
    print();
}

int ServiceQueue::peek() {
    if (isEmpty())
        throw "No elements";
    switch (preferred_dir) {
        case UP:
            for (int i = 0; i < ceil(position); i++)
                if (pending[i] && requests[i].direction == UP)
                    return requests[i].floor;
            for (int i = ceil(position); i < floors; i++)
                if (pending[i] && (requests[i].direction == NONE || requests[i].direction == UP))
                    return requests[i].floor;
            preferred_dir = DOWN;
            for (int i = floor(position); i >= 0; i--)
                if (pending[i] && (requests[i].direction == NONE || requests[i].direction == DOWN))
                    return requests[i].floor;
            break;
        case DOWN:
            for (int i = floors - 1; i > floor(position); i--)
                if (pending[i] && requests[i].direction == DOWN)
                    return requests[i].floor;
            for (int i = floor(position); i >= 0; i--)
                if (pending[i] && (requests[i].direction == NONE || requests[i].direction == DOWN))
                    return requests[i].floor;
            preferred_dir = UP;
            for (int i = ceil(position); i < floors; i++)
                if (pending[i] && (requests[i].direction == NONE || requests[i].direction == UP))
                    return requests[i].floor;
            break;
        case NONE:
            for (int i = 0; i < floors; i++)
                if (pending[i]) {
                    preferred_dir = requests[i].floor < position ? DOWN : UP;
                    return requests[i].floor;
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

void ServiceQueue::updatePosition(double position) {
    this->position = position;
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
    double cost = 0;
    for (int i = 0; i < floors; i++)
        if (pending[i])
            cost++;
    return cost;
}

