cmake_minimum_required(VERSION 3.24)
project(green_elevators)

set(CMAKE_CXX_STANDARD 17)

add_executable(green_elevators main.cpp utils/hardwareAPI.cpp utils/hardwareAPI.h workers/EventReceiver.cpp workers/EventReceiver.h workers/ElevatorController.cpp workers/ElevatorController.h structures/ActionQueue.cpp structures/ActionQueue.h structures/Action.cpp structures/Action.h utils/enums.h)
