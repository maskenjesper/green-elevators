#include "CommandSender.h"

ActionQueue *CommandSender::actionQueue;

pthread_t CommandSender::init(ActionQueue *actionQueue) {
    CommandSender::actionQueue = actionQueue;
    pthread_t tid;
    pthread_create(&tid, NULL, worker, NULL);
    return tid;
}

void *CommandSender::worker(void *) {
    while (true) {
        try {
            std::cout << "event sender: " << actionQueue->size() << " " << actionQueue->peek()->getElevator() << std::endl;
        }
        catch (std::out_of_range e) {
            std::cout << "empty" << std::endl;
        }
        sleep(5);
    }
}