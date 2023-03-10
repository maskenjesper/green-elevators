cmake_minimum_required(VERSION 3.24)
project(green_elevators)

set(CMAKE_CXX_STANDARD 17)

add_executable(green_elevators main.cpp utils/hardwareAPI.cpp utils/hardwareAPI.h workers/EventReceiver.cpp workers/EventReceiver.h workers/ElevatorController.cpp workers/ElevatorController.h structures/Request.cpp structures/Request.h utils/enums.h collections/ServiceQueue.cpp collections/ServiceQueue.h utils/CommandSender.cpp utils/CommandSender.h workers/CabinController.cpp workers/CabinController.h)
