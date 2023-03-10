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
    print();
}

int ServiceQueue::peek(double current_pos, Direction current_dir) {
    for (int i = 0; i < floors; i++)
        if (pending[i])
            return requests[i].floor;
    throw "No elements";
}

void ServiceQueue::pop(double current_pos, Direction current_dir) {
    for (int i = 0; i < floors; i++)
        if (pending[i]) {
            pending[i] = false;
            return;
        }
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

void ServiceQueue::clear() {
    for (int i = 0; i < floors; i++)
        pending[i] = false;
    print();
}

double ServiceQueue::cost(Request request, double current_pos, Direction current_dir) {
    return 0;
}

bool ServiceQueue::contains(int value) {

}

void ServiceQueue::remove(int value) {

}

