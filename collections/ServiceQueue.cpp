//
// Created by jakobolsson on 3/8/23.
//


#include "ServiceQueue.h"

ServiceQueue::ServiceQueue() {
    head = nullptr;
    turn = nullptr;
    tail = nullptr;
}

void ServiceQueue::push(Request request, double current_pos, Direction current_dir) {
    // If stop is already in queue, don't add it.
    contains(request.level);
    // If the queue is empty, just push it.
    if (isEmpty()) {
        std::cout << "added to empty" << std::endl;
        head = new Node(request.level, nullptr, nullptr);
        tail = head;
    }
        // If the queue is not empty, push to correct position.
    else {
        // If the stop can be made on the way.
        if ((request.type == DROPOFF || (request.type == PICKUP && request.direction == current_dir))
            && ((current_dir == UP && current_pos < request.level)
                || (current_dir == DOWN && current_pos > request.level))) {
            std::cout << "add on path: " << (current_dir == UP ? "Up" : "Down") << ", " << request.level << std::endl;
            pushOrdered(head, current_dir, request.level);
        }
            // If the stop needs to be made on the cabins return trip.
        else {
            std::cout << "add on return: " << (current_dir == UP ? "Up" : "Down") << ", " << request.level << std::endl;
            if (turn == nullptr) {
                Node* new_node = new Node(request.level, nullptr, tail);
                turn = new_node;
                tail->next = new_node;
                tail = new_node;
            }
            else
                pushOrdered(turn, current_dir == UP ? DOWN : UP, request.level);
        }
    }
    std::cout << "push: ";
    print();
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
        tail = nullptr;
    }
    else {
        Node* tmp = head;
        head = head->next;
        head->prev = nullptr;
        delete tmp;
    }
    if (head == turn)
        turn = nullptr;
    std::cout << "pop: ";
    print();
}

bool ServiceQueue::isEmpty() {
    return head == nullptr;
}

void ServiceQueue::print() {
    std::cout << "head: " << (head != nullptr ? head->value : -1)
              << ", turn: " << (turn != nullptr ? turn->value : -1)
              << ", tail: " << (tail != nullptr ? tail->value : -1) << " ";

    if (isEmpty()) {
        std::cout << "[]" << std::endl;
        return;
    }
    Node* current = head;
    std::cout << "[";
    while (current->next != nullptr) {
        std::cout << current->value << ", ";
        current = current->next;
    }
    std::cout << current->value << "]" << std::endl;
}

void ServiceQueue::pushOrdered(Node* from, Direction direction, int level) {
    if (direction == UP ? level < from->value : level > from->value) {
        std::cout << "add first" << std::endl;
        Node* new_node = new Node(level, from, from->prev);
        from->prev = new_node;
        if (new_node->prev != nullptr)
            new_node->prev->next = new_node;
        if (from == head)
            head = new_node;
        else
            turn = new_node;
    }
    else {
        Node* current = from;
        while (current->next != nullptr) {
            if (direction == UP ? level < current->value : level > current->value)
                break;
            current = current->next;
        }
        Node *new_node = new Node(level, current->next, current);
        if (current->next != nullptr)
            current->next->prev = new_node;
        else
            tail = new_node;
        current->next = new_node;
    }
}

void ServiceQueue::clear() {
    while (true) {
        try {
            pop();
        }
        catch (const char* e) {
            break;
        }
    }
}

double ServiceQueue::cost(Request request, double current_pos, Direction current_dir) {
    double cost = 0;
    if (isEmpty())
        return fabs(current_pos - request.level);
    else if (contains(request.level)) {
        cost += fabs(current_pos - head->value) + 0.1;
        Node* current = head;
        while (current->value != request.level) {
            cost += fabs(current->value - current->next->value) + 0.1;
            current = current->next;
        }
    }
    else {
        push(request, current_pos, current_dir);
        cost += fabs(current_pos - head->value) + 0.1;
        Node* current = head;
        while (current->value != request.level) {
            cost += fabs(current->value - current->next->value) + 0.1;
            current = current->next;
        }
        remove(request.level);
    }
    return cost;
}

bool ServiceQueue::contains(int value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->value == value)
            return true;
        current = current->next;
    }
    return false;
}

void ServiceQueue::remove(int value) {
    if (isEmpty())
        return;
    Node* current = head;
    while (current->next != nullptr) {
        if (current->value == value)
            break;
        current = current->next;
    }
    if (current->prev == nullptr) {
        pop();
    }
    else if (current->next == nullptr) {
        if (turn == tail)
            turn = nullptr;
        tail = tail->prev;
        tail->next = nullptr;
        delete current;
    }
    else {
        current->next->prev = current->prev;
        current->prev->next = current->next;
        delete current;
    }
}

