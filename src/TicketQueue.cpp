#include "TicketQueue.h"
#include <iostream>
TicketQueue::TicketQueue() {
    front = 0;
    rear = -1;
    count = 0;
}
bool TicketQueue::isEmpty() const {
    return count == 0;
}
bool TicketQueue::isFull() const {
    return count == CAPACITY;
}
int TicketQueue::size() const {
    return count;
}

bool TicketQueue::enqueue(Ticket ticket) {
    if (isFull()) {
        return false;
    }
    rear = (rear + 1) % CAPACITY;
    tickets[rear] = ticket;
    count++;
    return true;
}
bool TicketQueue::dequeue(Ticket& removedTicket) {
    if (isEmpty()) {
        return false;
    }
    removedTicket = tickets[front];
    front = (front + 1) % CAPACITY;
    count--;
    return true;
}

bool TicketQueue::cancel(int id, Ticket& removedTicket, int& position) {
    position = searchById(id);
    if (position == -1) {
        return false;
    }
    int index = (front + position - 1) % CAPACITY;
    removedTicket = tickets[index];
    for (int i = position - 1; i < count - 1; i++) {
        int current = (front + i) % CAPACITY;
        int next = (front + i + 1) % CAPACITY;
        tickets[current] = tickets[next];
    }
    rear = (rear - 1 + CAPACITY) % CAPACITY;
    count--;
    return true;
}

void TicketQueue::print() const {
    if (isEmpty()) {
        std::cout << "The queue is empty." << std::endl;
        return;
    }
    int totalMinutes = 0;
    std::cout << "\n--- Waiting Tickets ---\n";
    for (int i = 0; i < count; i++) {
        int index = (front + i) % CAPACITY;
        std::cout << "Position: " << i + 1
                  << " | ID: " << tickets[index].getId()
                  << " | Student: " << tickets[index].getStudentName()
                  << " | Category: " << tickets[index].getCategory()
                  << " | Minutes: " << tickets[index].getMinutesNeeded()
                  << std::endl;
        totalMinutes += tickets[index].getMinutesNeeded();
    }
    std::cout << "Total waiting minutes: "
              << totalMinutes << std::endl;
}

int TicketQueue::searchById(int id) const {
    for (int i = 0; i < count; i++) {
        int index = (front + i) % CAPACITY;
        if (tickets[index].getId() == id) {
            return i + 1;
        }
    }
    return -1;
}

int TicketQueue::searchByName(std::string name) const {
    for (int i = 0; i < count; i++) {
        int index = (front + i) % CAPACITY;
        if (tickets[index].getStudentName() == name) {
            return i + 1;
        }
    }
    return -1;
}

bool TicketQueue::insertAt(Ticket ticket, int position) {
    if (isFull() || position < 1 || position > count + 1) {
        return false;
    }
    for (int i = count; i >= position; i--) {
        int current = (front + i) % CAPACITY;
        int previous = (front + i - 1) % CAPACITY;
        tickets[current] = tickets[previous];
    }
    int index = (front + position - 1) % CAPACITY;
    tickets[index] = ticket;
    count++;
    rear = (front + count - 1) % CAPACITY;
    return true;
}

int TicketQueue::calculateWaitTime(int position) const {
    if (position < 1 || position > count) {
        return -1;
    }
    int totalMinutes = 0;
    for (int i = 0; i < position - 1; i++) {
        int index = (front + i) % CAPACITY;
        totalMinutes += tickets[index].getMinutesNeeded();
    }
    return totalMinutes;
}

