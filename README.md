# University IT Help Desk Ticket System
## Overview
A C++ program that simulates a university IT help desk. The system manages student support tickets using a queue and supports adding, serving, searching, cancelling, and undoing ticket actions.
## Data Structures
- **Ticket:** Stores the ticket ID, student name, category, and estimated service time.
- **TicketQueue:** Uses a circular array to manage waiting tickets.
- **ActionStack:** Uses an array-based stack to support undoing the most recent add, serve, or cancel action.
- **Simulation:** Compares ticket wait times when using one versus two help desk agents.
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
## Simulation Results
Using the sample tickets in `data/sample_tickets.csv`:
| Metric | One Agent | Two Agents |
|---|---:|---:|
| Tickets processed | 5 | 5 |
| Average wait | 33.00 minutes | 12.00 minutes |
| Longest wait | 70 minutes | 25 minutes |
**Simulation assumption:** All tickets are assumed to arrive at the beginning of the simulation and are assigned in CSV order to the agent who becomes available first.
