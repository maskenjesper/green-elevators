//
// Created by jakobolsson on 3/3/23.
//

#ifndef GREEN_ELEVATORS_ACTION_H
#define GREEN_ELEVATORS_ACTION_H


class Action {
public:
    enum Direction {
        UP, DOWN, NONE
    };
    enum Type {
        PICKUP, DROPOFF
    };
private:
    int level, elevator;
    Direction direction;
    Type type;

public:
    Action(int floor, int elevator, Direction direction, Type type);
    int getFloor();
    int getElevator();
    Direction getDirection();
    Type getType();
};


#endif //GREEN_ELEVATORS_ACTION_H
