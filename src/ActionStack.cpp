#include "ActionStack.h"

ActionStack::ActionStack() {
    top = -1;
}
bool ActionStack::isEmpty() const {
    return top == -1;
}
bool ActionStack::isFull() const {
    return top == CAPACITY - 1;
}
int ActionStack::size() const {
    return top + 1;
}
bool ActionStack::push(Action action) {
    if (isFull()) {
        return false;
    }
    top++;
    actions[top] = action;
    return true;
}
bool ActionStack::pop(Action& removedAction) {
    if (isEmpty()) {
        return false;
    }
    removedAction = actions[top];
    top--;
    return true;
}
