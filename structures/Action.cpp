//
// Created by jakobolsson on 3/3/23.
//

#include "Action.h"


Action::Action(int floor, int elevator, Direction direction, Type type) {
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

Action::Direction Action::getDirection() {
    return this->direction;
}

Action::Type Action::getType() {
    return this->type;
}