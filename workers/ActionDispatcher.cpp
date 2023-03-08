//
// Created by jakobolsson on 3/7/23.
//

#include "ActionDispatcher.h"

pthread_t ActionDispatcher::tid;
std::queue<Action> ActionDispatcher::actions;
pthread_mutex_t ActionDispatcher::lock;
pthread_cond_t ActionDispatcher::cond;

void ActionDispatcher::init() {
    pthread_create(&tid, nullptr, worker, nullptr);
}

void ActionDispatcher::quit() {
    pthread_join(tid, nullptr);
}

void *ActionDispatcher::worker(void *) {
    pthread_mutex_lock(&lock);
    while (true) {
        if (actions.size() > 0) {
            Action action = actions.front();
            actions.pop();
            switch (action.type) {
                case PICKUP:
                    std::cout << "Dispatch new action: pickup, " << action.elevator << ", " << action.level << std::endl;
                    // TODO: Determine best cabin to service request
                    ElevatorController::addStop(1, action.level);
                    break;
                case DROPOFF:
                    std::cout << "Dispatch new action: dropoff, " << action.elevator << ", " << action.level << std::endl;
                    ElevatorController::addStop(action.elevator, action.level);
                    break;
            }
        }
        pthread_cond_wait(&cond, &lock);
    }
    pthread_mutex_unlock(&lock);
}

void ActionDispatcher::addAction(const Action* action) {
    pthread_mutex_lock(&lock);
    actions.push(*action);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
}
