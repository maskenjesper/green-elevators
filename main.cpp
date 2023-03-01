#include <iostream>

#include "utils/hardwareAPI.h"

int main() {
    initHW((char*) "127.0.0.1", 4711);
    EventDesc event;
    waitForEvent(&event);
    std::cout << "Hello, World!" << std::endl;
}
