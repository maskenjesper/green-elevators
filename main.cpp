#include <iostream>

#include "utils/hardwareAPI.h"
#include "workers/CommandReceiver.h"
#include "workers/CommandSender.h"
#include "structures/ActionQueue.h"

int main() {
    initHW((char*) "127.0.0.1", 4711);

    auto *actionQueue = new ActionQueue();

    // Starts the command receiver thread
    pthread_t er = CommandReceiver::init(actionQueue);
    // Starts the command sender thread
    pthread_t cs = CommandSender::init(actionQueue);

    pthread_join(er, NULL);
    pthread_join(cs, NULL);
    free(actionQueue);
}
