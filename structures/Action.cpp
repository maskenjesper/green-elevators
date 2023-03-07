//
// Created by jakobolsson on 3/3/23.
//

#include "Action.h"


Action::Action(int floor, int elevator, CabinDirection direction, ActionType type) {
    this->level = floor;
    this->elevator = elevator;
    this->direction = direction;
    this->type = type;
}

int Action::getFloor() {
    return this->level;
}

int Action::getElevator() {
    return this->elevator;
}

CabinDirection Action::getDirection() {
    return this->direction;
}

ActionType Action::getType() {
    return this->type;
}