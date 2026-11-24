#include "Ticket.h"
Ticket::Ticket(int id, std::string studentName,
               std::string category, int minutesNeeded) {
    this->id = id;
    this->studentName = studentName;
    this->category = category;
    this->minutesNeeded = minutesNeeded;
}
int Ticket::getId() const {
    return id;
}
std::string Ticket::getStudentName() const {
    return studentName;
}
std::string Ticket::getCategory() const {
    return category;
}
int Ticket::getMinutesNeeded() const {
    return minutesNeeded;
}