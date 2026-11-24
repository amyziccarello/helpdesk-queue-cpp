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
#include "Simulation.h"
#include <iomanip>
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
        cout << "7. Load Tickets from CSV\n";
        cout << "8. Save Tickets to CSV\n";
        cout << "9. Run Agent Simulation\n";
        cout << "10. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                if (actionStack.isFull()) {
                    cout << "Action history is full. Cannot add ticket.\n";
                    break;
                }
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
                if (actionStack.isFull()) {
                    cout << "Action history is full. Cannot add ticket.\n";
                    break;
                }
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
                if (actionStack.isFull()) {
                    cout << "Action history is full. Cannot cancel ticket.\n";
                    break;
                }
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
                    bool success = false;
                    if (lastAction.type == "ADD") {
                        Ticket removedTicket;
                        int position;
                        success = queue.cancel(
                        lastAction.ticket.getId(),
                        removedTicket,
                        position
                    );
                }
                    else if (lastAction.type == "SERVE") {
                        success = queue.insertAt(lastAction.ticket, 1);
                    }
                    else if (lastAction.type == "CANCEL") {
                        success = queue.insertAt(
                        lastAction.ticket,
                        lastAction.position
                    );
                }
                if (success) {
                    cout << "Last " << lastAction.type
                         << " action undone successfully.\n";
                }
                else {
                    actionStack.push(lastAction);
                    cout << "Undo failed. Action restored to stack.\n";
                }
            }
            else {
                cout << "There are no actions to undo.\n";
            }
            break;
        }
            case 7: {
                ifstream inputFile("data/sample_tickets.csv");
                if (!inputFile.is_open()) {
                    cout << "Could not open CSV file.\n";
                    break;
                }
                string line;
                getline(inputFile, line); // Skip header
                int loaded = 0;
                while (getline(inputFile, line)) {
                    stringstream ss(line);      
                    string idText, name, category, minutesText;
                    getline(ss, idText, ',');
                    getline(ss, name, ',');
                    getline(ss, category, ',');
                    getline(ss, minutesText, ',');

                    if (idText.empty() || name.empty() ||
                        category.empty() || minutesText.empty()) {
                        continue;
                    }
                    int id = stoi(idText);
                    int minutes = stoi(minutesText);
                    Ticket ticket(id, name, category, minutes);
                    if (queue.enqueue(ticket)) {
                        loaded++;
                        if (id >= nextId) {
                            nextId = id + 1;
                        }
                    }
                    else {
                        cout << "Queue is full. Some tickets were not loaded.\n";
                        break;
                    }
                }

                inputFile.close();
                cout << loaded << " tickets loaded successfully.\n";
                break;
            }
            case 8: {
                ofstream outputFile("data/saved_tickets.csv");
                if (!outputFile.is_open()) {
                    cout << "Could not save CSV file.\n";
                    break;
                }   
                outputFile << "id,studentName,category,minutesNeeded\n";
                for (int i = 1; i <= queue.size(); i++) {
                    Ticket ticket = queue.getAtPosition(i);
                    outputFile << ticket.getId() << ","
                               << ticket.getStudentName() << ","
                               << ticket.getCategory() << ","
                               << ticket.getMinutesNeeded() << "\n";
                }
                outputFile.close();
                cout << "Tickets saved successfully!\n";
                break;
            }
            case 9: {
                SimulationResult oneAgent =
                Simulation::runSimulation("data/sample_tickets.csv", 1);
                SimulationResult twoAgents = Simulation::runSimulation("data/sample_tickets.csv", 2);
                cout << fixed << setprecision(2);
                cout << "\n===== SIMULATION RESULTS =====\n";
                cout << "\nONE AGENT:\n";
                cout << "Tickets processed: "
                     << oneAgent.totalTickets << endl;
                cout << "Average wait: "
                     << oneAgent.averageWait << " minutes\n";
                cout << "Longest wait: "
                     << oneAgent.longestWait << " minutes\n";
                cout << "\nTWO AGENTS:\n";
                cout << "Tickets processed: "
                     << twoAgents.totalTickets << endl;
                cout << "Average wait: "
                     << twoAgents.averageWait << " minutes\n";
                cout << "Longest wait: "
                     << twoAgents.longestWait << " minutes\n";
                break;
            }
            case 10:
                cout << "Exiting help desk system.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 10);
    return 0;
}
