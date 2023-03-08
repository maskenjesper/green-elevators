//
// Created by jakobolsson on 3/8/23.
//

#include <algorithm>
#include <iostream>
#include "ServiceQueue.h"

ServiceQueue::ServiceQueue() {
    head = nullptr;
}

void ServiceQueue::push(Action action, double current_pos, Direction current_dir) {
    Node* current = head;
    switch (current_dir) {
        case UP:
            while (current->next != nullptr) {
                if (action.level > current->next->value) {
                    Node* new_node = new Node(action.level, current->next->next);
                    current->next = new_node;
                }
                current = current->next;
            }
            break;
        case DOWN:
            break;
        case NONE:
            std::cout << "head should be null: " << (head == nullptr) << std::endl;
            head = new Node(action.level, nullptr);
            break;
    }
}

int ServiceQueue::peek() {
    if (isEmpty())
        throw "No elements";
    else
        return head->value;
}

void ServiceQueue::pop() {
    if (isEmpty())
        throw "No elements";
    else if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

bool ServiceQueue::isEmpty() {
   return head == nullptr;
}

