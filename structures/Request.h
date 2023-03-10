//
// Created by jakobolsson on 3/3/23.
//

#ifndef GREEN_ELEVATORS_REQUEST_H
#define GREEN_ELEVATORS_REQUEST_H


#include "../utils/enums.h"

struct Request {
    int level, elevator;
    Direction direction;
    ActionType type;

public:
    Request(int floor, int elevator, Direction direction, ActionType type);
};


#endif //GREEN_ELEVATORS_REQUEST_H
