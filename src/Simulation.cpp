#include "Simulation.h"
#include <iostream>
#include <fstream>
#include <sstream>
SimulationResult Simulation::runSimulation(
    std::string filename,
    int numberOfAgents
) {
    SimulationResult result;
    result.totalTickets = 0;
    result.averageWait = 0;
    result.longestWait = 0;
    if (numberOfAgents < 1 || numberOfAgents > 2) {
        std::cout << "Invalid number of agents.\n";
        return result;
    }
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cout << "Could not open CSV file.\n";
        return result;
    }
    int agentAvailable[2] = {0, 0};
    std::string line;
    std::getline(inputFile, line);
    int totalWait = 0;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string idText;
        std::string name;
        std::string category;
        std::string minutesText;
        std::getline(ss, idText, ',');
        std::getline(ss, name, ',');
        std::getline(ss, category, ',');
        std::getline(ss, minutesText, ',');
        if (idText.empty() || minutesText.empty()) {
            continue;
        }
        int minutes = std::stoi(minutesText);
        int selectedAgent = 0;
        for (int i = 1; i < numberOfAgents; i++) {
            if (agentAvailable[i] <
                agentAvailable[selectedAgent]) {
                selectedAgent = i;
            }
        }
        int waitTime = agentAvailable[selectedAgent];
        totalWait += waitTime;
        if (waitTime > result.longestWait) {
            result.longestWait = waitTime;
        }
        agentAvailable[selectedAgent] += minutes;
        result.totalTickets++;
    }
    inputFile.close();
    if (result.totalTickets > 0) {
        result.averageWait =
            static_cast<double>(totalWait) / result.totalTickets;
    }
    return result;
}
