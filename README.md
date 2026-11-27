# University IT Help Desk Ticket System

## Overview
A C++ program that simulates a university IT help desk. The system manages student support tickets using a queue and supports adding, serving, searching, cancelling, and undoing ticket actions.

## Data Structures
* **Ticket:** Stores the ticket ID, student name, category, and estimated service time.
* **TicketQueue:** Uses a circular array to manage waiting tickets.
* **ActionStack:** Uses an array-based stack to support undoing the most recent add, serve, or cancel action.
* **Simulation:** Compares ticket wait times when using one versus two help desk agents.

## Features
1. Add a new ticket
2. Serve the next ticket
3. Print all waiting tickets and total waiting minutes
4. Search tickets by ID or student name
5. Cancel a ticket
6. Undo the last add, serve, or cancel action
7. Load tickets from a CSV file
8. Save waiting tickets to a CSV file
9. Simulate wait times with one and two agents

## Build and Run Instructions

This project is written in C++ and does not require any external libraries. To compile and run the program, use the following commands in your terminal:

```bash
# 1. Compile the source files. 
# (Make sure you are in the root directory of the project)
g++ -std=c++11 src/*.cpp -o helpdesk

# 2. Run the executable
./helpdesk

Sample Session
Below is an example of how a user session looks when adding a ticket, viewing the queue, and undoing an action:
=== UNIVERSITY IT HELP DESK ===
1. Add Ticket
2. Serve Ticket
3. Print Waiting Tickets
4. Search Ticket
5. Cancel Ticket
6. Undo Last Action
7. Load Tickets from CSV
8. Save Tickets to CSV
9. Run Agent Simulation
10. Exit

Enter your choice: 1
Enter student name: Alice Smith
Enter ticket category: Wi-Fi Problem
Enter estimated minutes needed: 15
Ticket added successfully!
Ticket ID: 1

Enter your choice: 1
Enter student name: Bob Jones
Enter ticket category: Password Reset
Enter estimated minutes needed: 10
Ticket added successfully!
Ticket ID: 2

Enter your choice: 3

--- Waiting Tickets ---
Position: 1 | ID: 1 | Student: Alice Smith | Category: Wi-Fi Problem | Minutes: 15
Position: 2 | ID: 2 | Student: Bob Jones | Category: Password Reset | Minutes: 10
Total waiting minutes: 25

Enter your choice: 6
Undo successful! Ticket ID: 2 removed.

Enter your choice: 3

--- Waiting Tickets ---
Position: 1 | ID: 1 | Student: Alice Smith | Category: Wi-Fi Problem | Minutes: 15
Total waiting minutes: 15

Enter your choice: 10
Exiting system. Goodbye!

Simulation Results
Using the sample tickets in data/sample_tickets.csv:

Metric	One Agent	Two Agents
Tickets processed	5	5
Average wait	33.00 minutes	12.00 minutes
Longest wait	70 minutes	25 minutes
Simulation assumption: All tickets are assumed to arrive at the beginning of the simulation and are assigned in CSV order to the agent who becomes available first.
