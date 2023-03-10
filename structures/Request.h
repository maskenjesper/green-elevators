//
// Created by jakobolsson on 3/3/23.
//

#ifndef GREEN_ELEVATORS_REQUEST_H
#define GREEN_ELEVATORS_REQUEST_H


#include "../utils/enums.h"

struct Request {
    int floor, cabin;
    Direction direction;
    ActionType type;

public:
    Request();
    Request(int floor, int cabin, Direction direction, ActionType type);
};


#endif //GREEN_ELEVATORS_REQUEST_H
