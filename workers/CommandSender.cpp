#include "CommandSender.h"

pthread_t CommandSender::init(ActionQueue actionQueue) {
    CommandSender::actionQueue = actionQueue;
    pthread_t tid;
    pthread_create(&tid, NULL, worker, NULL);
    return tid;
}

void *CommandSender::worker(void *) {
    while (true) {
        std::cout << "event sender" << std::endl;
        sleep(5);
    }
}