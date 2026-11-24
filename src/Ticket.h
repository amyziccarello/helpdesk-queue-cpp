#ifndef TICKET_H
#define TICKET_H
#include <string>
class Ticket {
private:
    int id;
    std::string studentName;
    std::string category;
    int minutesNeeded;
public:
    Ticket();
    Ticket(int id, std::string studentName, std::string category, int minutesNeeded);
    int getId() const;
    std::string getStudentName() const;
    std::string getCategory() const;
    int getMinutesNeeded() const;
};
#endif
