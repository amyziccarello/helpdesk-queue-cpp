/*
//initial tests for basic funcs
#include <iostream>
#include "Ticket.h"
#include "TicketQueue.h"

using namespace std;

int main() {
    TicketQueue queue;
    Ticket t1(1, "Amy", "Wi-Fi", 15);
    Ticket t2(2, "Mike", "Printer", 20);
    Ticket t3(3, "Lingtong", "Password Reset", 10);
    queue.enqueue(t1);
    queue.enqueue(t2);
    queue.enqueue(t3);
    cout << "Initial Queue:" << endl;
    queue.print();
    cout << "\nSearching for ticket ID 2: "
         << queue.searchById(2) << endl;

    cout << "Searching for Mike: "
         << queue.searchByName("Mike") << endl;

    // Test dequeue
    Ticket removedTicket;

    queue.dequeue(removedTicket);

    cout << "\nServed ticket: "
         << removedTicket.getStudentName() << endl;

    // Print updated queue
    cout << "\nUpdated Queue:" << endl;
    queue.print();

    return 0;
}
*/

#include <iostream>
#include <string>
#include "Ticket.h"
#include "TicketQueue.h"
#include "ActionStack.h"
#include <fstream>
#include <sstream>
using namespace std;
int main() {
    TicketQueue queue;
    ActionStack actionStack;
    int nextId = 1;
    int choice;
    do {
        cout << "\n===== UNIVERSITY IT HELP DESK =====\n";
        cout << "1. Add Ticket\n";
        cout << "2. Serve Ticket\n";
        cout << "3. Print Waiting Tickets\n";
        cout << "4. Search Ticket\n";
        cout << "5. Cancel Ticket\n";
        cout << "6. Undo Last Action\n";
        cout << "7. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string name;
                string category;
                int minutes;
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter ticket category: ";
                getline(cin, category);
                cout << "Enter estimated minutes needed: ";
                cin >> minutes;

                Ticket newTicket(nextId, name, category, minutes);
                if (queue.enqueue(newTicket)) {
                    Action action;
                    action.type = "ADD";
                    action.ticket = newTicket;
                    action.position = queue.size();
                    actionStack.push(action);
                    cout << "Ticket added successfully!"
                        << " Ticket ID: " << nextId << endl;

                    nextId++;
                }
                else {
                    cout << "Queue is full. Ticket could not be added.\n";
                }

                break;
            }

            case 2: {
                Ticket servedTicket;
                if (queue.dequeue(servedTicket)) {
                    Action action;
                    action.type = "SERVE";
                    action.ticket = servedTicket;
                    action.position = 1;
                    actionStack.push(action);

                    cout << "Ticket served successfully!\n";
                    cout << "Student: " << servedTicket.getStudentName() << endl;
                    cout << "Ticket ID: " << servedTicket.getId() << endl;
                }
                else {
                    cout << "There are no tickets waiting.\n";
                }
                break;
            }

            case 3: {
                queue.print();
                break;
            }
            case 4: {
                int searchChoice;
                cout << "\nSearch by:\n";
                cout << "1. Ticket ID\n";
                cout << "2. Student Name\n";
                cout << "Enter choice: ";
                cin >> searchChoice;
                int position = -1;
                if (searchChoice == 1) {
                    int id;
                    cout << "Enter ticket ID: ";
                    cin >> id;
                    position = queue.searchById(id);
                }
                else if (searchChoice == 2) {
                    string name;
                    cout << "Enter student name: ";
                    cin.ignore();
                    getline(cin, name);
                    position = queue.searchByName(name);
                }
                else {
                    cout << "Invalid search option.\n";
                    break;
                }

                if (position != -1) {
                    int waitTime = queue.calculateWaitTime(position);
                    cout << "\nTicket found!\n";
                    cout << "Position in line: " << position << endl;
                    cout << "Estimated wait: " << waitTime
                    << " minutes\n";
                }
                else {
                    cout << "Ticket not found.\n";
                }
                break;
            }
        
            
            case 5: {
                int id;
                cout << "Enter ticket ID to cancel: ";
                cin >> id;
                Ticket cancelledTicket;
                int position;
                if (queue.cancel(id, cancelledTicket, position)) {
                Action action;
                action.type = "CANCEL";
                action.ticket = cancelledTicket;
                action.position = position;
                actionStack.push(action);
                cout << "Ticket cancelled successfully!\n";
                cout << "Student: "
                    << cancelledTicket.getStudentName() << endl;
                cout << "Original position: " << position << endl;
            }
            else {
                cout << "Ticket ID not found.\n";
            }
            break;
        }

        
            
            case 6: {
                Action lastAction;
                if (actionStack.pop(lastAction)) {
                    if (lastAction.type == "ADD") {
                        Ticket removedTicket;
                            int position;
                            queue.cancel(lastAction.ticket.getId(), removedTicket, position);
                            cout << "Last ADD action undone.\n";
                        }

                    else if (lastAction.type == "SERVE") {
                        queue.insertAt(lastAction.ticket, 1);
                        cout << "Last SERVE action undone.\n";
                    }
                    else if (lastAction.type == "CANCEL") {
                        queue.insertAt(lastAction.ticket, lastAction.position);
                        cout << "Last CANCEL action undone.\n";
                    }
                }
                else {
                    cout << "There are no actions to undo.\n";
                }
                break;
            }

            case 7:
                cout << "Exiting help desk system.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);
    return 0;
}
