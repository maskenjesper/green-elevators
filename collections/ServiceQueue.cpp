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
}

void ServiceQueue::push(Request request) {
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

int ServiceQueue::peek(double current_pos, Direction current_dir) {
    if (isEmpty())
        throw "No elements";
    switch (current_dir) {
        case UP:
            for (int i = ceil(current_pos); i < floors; i++)
                if (pending[i] && (requests[i].direction == NONE || requests[i].direction == UP))
                    return requests[i].floor;
            if (pending[floors - 1])
                return requests[floors - 1].floor;
            return -1;

        case DOWN:
            for (int i = floor(current_pos); i >= 0; i--)
                if (pending[i] && (requests[i].direction == NONE || requests[i].direction == DOWN))
                    return requests[i].floor;
            if (pending[0])
                return requests[0].floor;
            return -1;
        case NONE:
            for (int i = 0; i < floors; i++)
                if (pending[i])
                    return requests[i].floor;
            break;
    }
}

void ServiceQueue::pop(double current_pos, Direction current_dir) {
    pending[peek(current_pos, current_dir)] = false;
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

double ServiceQueue::cost(Request request, double current_pos, Direction current_dir) {
    double cost = 0;
    for (int i = 0; i < floors; i++)
        if (pending[i])
            cost++;
    return cost;
}

