#pragma once
#include "../config/Config.h"
#include "../memory/PageTable.h"
#include "../memory/FrameManager.h"
#include "../memory/TLB.h"
#include "../algorithms/Replacement.h"
#include "../algorithms/ReplacementFactory.h"

#include <vector>
#include <unordered_map>
#include <queue>
#include <string>

class Simulator {
private:
    Config config;

    PageTable pageTable;
    FrameManager frameManager;
    TLB tlb;  

    Replacement* algo;

    // For OPT and frame tracking
    std::unordered_map<int, std::queue<int>> futureUse;
    std::vector<int> frames; // frame -> vpn mapping

    // Stats
    int hits = 0;
    int tlbHits = 0; // Track TLB specifically for EAT 
    int faults = 0;
    int diskWrites = 0;
    long long totalTime = 0;

public:
    Simulator(Config c, const std::string& algoType);
    ~Simulator(); // Destructor to clean up 'algo' pointer 
    void run(const std::string& traceFile);

private:
    void preprocessOPT(const std::vector<std::pair<unsigned int,char>>& traceVec);
    void printStats();
};