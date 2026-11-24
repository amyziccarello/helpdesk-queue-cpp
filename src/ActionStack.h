#ifndef ACTIONSTACK_H
#define ACTIONSTACK_H
#include "Ticket.h"
struct Action {
    std::string type;
    Ticket ticket;
    int position;
};
class ActionStack {
private:
    static const int CAPACITY = 100;
    Action actions[CAPACITY];
    int top;
public:
    ActionStack();
    bool isEmpty() const;
    bool isFull() const;
    int size() const;
    bool push(Action action);
    bool pop(Action& removedAction);
};
#endif
