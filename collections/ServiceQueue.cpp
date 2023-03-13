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
}

int ServiceQueue::peek() {
    if (isEmpty())
        throw "No elements";
    int next_floor;
    switch (preferred_dir) {
        case UP:
            next_floor = checkForRequest();
            if (next_floor == -1) {
                preferred_dir = DOWN;
                return checkForRequest();
            }
            else
                return next_floor;
        case DOWN:
            next_floor = checkForRequest();
            if (next_floor == -1) {
                preferred_dir = UP;
                return checkForRequest();
            }
            else
                return next_floor;
        case NONE:
            for (int i = 0; i < floors; i++)
                if (pending[i]) {
                    preferred_dir = i < position ? DOWN : UP;
                    return i;
                }
            break;
    }
}

int ServiceQueue::checkForRequest() {
    switch (preferred_dir) {
        case UP:
            for (int i = ceil(position); i < floors; i++)
                if (pending[i] && (type[i] == NONE || type[i] == UP))
                    return i;
            for (int i = floors - 1; i >= ceil(position); i--)
                if (pending[i] && (type[i] == NONE || type[i] == DOWN))
                    return i;
            return -1;
        case DOWN:
            for (int i = floor(position); i >= 0; i--)
                if (pending[i] && (type[i] == NONE || type[i] == DOWN))
                    return i;
            for (int i = 0; i <= floor(position); i++)
                if (pending[i] && (type[i] == NONE || type[i] == UP))
                    return i;
            return -1;
    }
}

void ServiceQueue::pop() {
    pending[peek()] = false;
    if (isEmpty())
        preferred_dir = NONE;
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
    // Saving state
    Backup* backup = new Backup(type, pending, floors, preferred_dir, position);
    // Calculate cost
    push(request);
    int next_floor = peek(); pop();
    if (type[next_floor] == UP)
        push(Request(floors - 1, 1, NONE, DROPOFF));
    else if (type[next_floor] == DOWN)
        push(Request(0, 1, NONE, DROPOFF));
    double cost = fabs(position - next_floor);
    if (type[request.floor] == UP && request.direction == DOWN
             || type[request.floor] == DOWN && request.direction == UP) {
        cost += 10;
    }
    position = next_floor;
    while (next_floor != request.floor) {
        next_floor = peek(); pop();
        if (type[next_floor] == UP)
            push(Request(floors - 1, 1, NONE, DROPOFF));
        else if (type[next_floor] == DOWN)
            push(Request(0, 1, NONE, DROPOFF));
        cost += fabs(position - next_floor);
        position = next_floor;
    }
    // Restore state
    restore(backup);
    return cost;
}

void ServiceQueue::restore(Backup* backup) {
    for (int i = 0; i < floors; i++) {
        type[i] = backup->type[i];
        pending[i] = backup->pending[i];
    }
    floors = backup->floors;
    preferred_dir = backup->preferred_dir;
    position = backup->position;
    delete backup;
}

