//
// Created by jakobolsson on 3/3/23.
//

#ifndef GREEN_ELEVATORS_ACTION_H
#define GREEN_ELEVATORS_ACTION_H


#include "../utils/enums.h"

struct Action {
    int level, elevator;
    Direction direction;
    ActionType type;

public:
    Action(int floor, int elevator, Direction direction, ActionType type);
};


#endif //GREEN_ELEVATORS_ACTION_H
