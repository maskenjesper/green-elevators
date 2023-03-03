#include <iostream>

#include "utils/hardwareAPI.h"
#include "workers/CommandReceiver.h"
#include "workers/CommandSender.h"
#include "structures/ActionQueue.h"

int main() {
    initHW((char*) "127.0.0.1", 4711);

//    ActionQueue actionQueue = ActionQueue();

    pthread_t er = CommandReceiver::init();
    pthread_t cs = CommandSender::init();

    pthread_join(er, NULL);
    pthread_join(cs, NULL);
}
