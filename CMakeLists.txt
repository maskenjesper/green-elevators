cmake_minimum_required(VERSION 3.24)
project(green_elevators)

set(CMAKE_CXX_STANDARD 17)

add_executable(green_elevators main.cpp utils/hardwareAPI.cpp utils/hardwareAPI.h workers/CommandReceiver.cpp workers/CommandReceiver.h workers/CommandSender.cpp workers/CommandSender.h structures/ActionQueue.cpp structures/ActionQueue.h structures/Action.cpp structures/Action.h utils/hardwareAPI.cpp utils/hardwareAPI.h)
