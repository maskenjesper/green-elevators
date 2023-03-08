//
// Created by jakobolsson on 3/3/23.
//

#include "Action.h"


Action::Action(int floor, int elevator, Direction direction, ActionType type) {
    this->level = floor;
    this->elevator = elevator;
    this->direction = direction;
    this->type = type;
}