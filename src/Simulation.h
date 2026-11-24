#ifndef SIMULATION_H
#define SIMULATION_H
#include <string>
struct SimulationResult {
    int totalTickets;
    double averageWait;
    int longestWait;
};
class Simulation {
public:
    static SimulationResult runSimulation(
        std::string filename,
        int numberOfAgents
    );
};
#endif
