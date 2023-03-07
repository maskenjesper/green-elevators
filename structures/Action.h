//
// Created by jakobolsson on 3/3/23.
//

#ifndef GREEN_ELEVATORS_ACTION_H
#define GREEN_ELEVATORS_ACTION_H


#include "../utils/enums.h"

class Action {
private:
    int level, elevator;
    CabinDirection direction;
    ActionType type;

public:
    Action(int floor, int elevator, CabinDirection direction, ActionType type);
    int getFloor();
    int getElevator();
    CabinDirection getDirection();
    ActionType getType();
};


#endif //GREEN_ELEVATORS_ACTION_H
