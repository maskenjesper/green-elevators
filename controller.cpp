#include <stdio.h>

#include "utils/hardwareAPI.h"

int main(int argc, char const *argv[]) {
    initHW((char*)"127.0.0.1", 4711);
    EventDesc desc;
    waitForEvent(&desc);
    printf("hello");
}
