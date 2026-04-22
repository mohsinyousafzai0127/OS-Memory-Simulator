#include <iostream>
#include <string>
#include <vector>
#include "config/Config.h"
#include "simulator/Simulator.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: ./simulator <config_file> <trace_file> [algorithm]\n";
        cout << "Algorithms: FIFO, LRU, OPT\n";
        return 1;
    }

    string configFile = argv[1];
    string traceFile = argv[2];
    
    // Default to LRU if no algorithm is specified
    string algoType = (argc >= 4) ? argv[3] : "LRU";

    try {
        cout << "--- Initializing Simulation ---\n";
        Config config = Config::loadFromFile(configFile);
        
        cout << "RAM Size:    " << config.RAM_SIZE << " bytes\n";
        cout << "Page Size:   " << config.PAGE_SIZE << " bytes\n";
        cout << "Frames:      " << config.numFrames << "\n";
        cout << "Algorithm:   " << algoType << "\n";
        cout << "-------------------------------\n";

        // Create and Run Simulator
        Simulator sim(config, algoType);
        sim.run(traceFile);

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}