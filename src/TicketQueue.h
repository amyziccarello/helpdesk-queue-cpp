#ifndef TICKETQUEUE_H
#define TICKETQUEUE_H
#include "Ticket.h"
class TicketQueue {
private:
    static const int CAPACITY = 100;

    Ticket tickets[CAPACITY];
    int front;
    int rear;
    int count;
public:
    TicketQueue();
    bool isEmpty() const;
    bool isFull() const;
    int size() const;
    bool enqueue(Ticket ticket);
    bool dequeue(Ticket& removedTicket);
    bool cancel(int id, Ticket& removedTicket, int& position);
    bool insertAt(Ticket ticket, int position);
    void print() const;
    int searchById(int id) const;
    int searchByName(std::string name) const;
    int calculateWaitTime(int position) const;
};


#endif
