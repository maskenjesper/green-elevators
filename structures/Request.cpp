#include "Request.h"


Request::Request(int floor, int cabin, Direction direction, ActionType type) {
    this->floor = floor;
    this->cabin = cabin;
    this->direction = direction;
    this->type = type;
}

Request::Request() {

}
