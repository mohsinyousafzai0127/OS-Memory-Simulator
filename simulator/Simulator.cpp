#include "Simulator.h"
#include "../memory/Address.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Simulator::Simulator(Config c, const string& algoType)
    : config(c), frameManager(c.numFrames), tlb(c.TLB_SIZE) 
{
    frames.resize(config.numFrames, -1);
    algo = ReplacementFactory::create(algoType, futureUse, &frames); 
}

Simulator::~Simulator() {
    delete algo; // Memory cleanup 
}

void Simulator::preprocessOPT(const vector<pair<unsigned int,char>>& traceVec) {
    for (int i = 0; i < traceVec.size(); i++) {
        int vpn = Address::getVPN(traceVec[i].first, config.offsetBits); 
        futureUse[vpn].push(i);
    }
}

void Simulator::run(const string& traceFile) {
    ifstream file(traceFile);
    string line;
    vector<pair<unsigned int,char>> traceVec;

    // Load Trace
    while (getline(file, line)) {
        stringstream ss(line);
        string addrStr;
        char op;
        ss >> addrStr >> op;
        traceVec.push_back({stoul(addrStr, nullptr, 16), op});
    }

    preprocessOPT(traceVec);

    for (int i = 0; i < traceVec.size(); i++) {
        unsigned int addr = traceVec[i].first;
        char op = traceVec[i].second;
        int vpn = Address::getVPN(addr, config.offsetBits);

        bool found = false;
        int frame = -1;

        // TLB LOOKUP 
        frame = tlb.lookup(vpn);
        if (frame != -1) {
            tlbHits++;
            hits++;
            totalTime += config.TLB_LATENCY;
            found = true;
        } 
        // PAGE TABLE LOOKUP (TLB MISS) 
        else {
            totalTime += config.TLB_LATENCY; // Time spent checking TLB
            if (pageTable.isValid(vpn)) {
                hits++;
                totalTime += config.RAM_LATENCY;
                frame = pageTable.get(vpn).frame;
                tlb.insert(vpn, frame); // Update TLB 
                found = true;
            }
        }

        // PAGE FAULT 
        if (!found) {
            faults++;
            totalTime += config.RAM_LATENCY; // PT Check time

            if (frameManager.hasFreeFrame()) {
                frame = frameManager.allocate(); 
            } else {
                int victimVPN = algo->evict(); 
                PTE &victim = pageTable.get(victimVPN);

                if (victim.dirty) {
                    diskWrites++;
                    totalTime += config.DISK_LATENCY;
                }
                
                frame = victim.frame;
                pageTable.invalidate(victimVPN); 
                tlb.invalidate(victimVPN);  
            }

            totalTime += config.DISK_LATENCY; // Load from disk
            pageTable.get(vpn) = {true, false, frame};
            tlb.insert(vpn, frame);
            frames[frame] = vpn;
        }

        // Update algorithm (for LRU/OPT logic) 
        algo->access(vpn);

        if (op == 'W') {
            pageTable.get(vpn).dirty = true;
        }
    }
    printStats();
}

void Simulator::printStats() {
    int totalAccesses = hits + faults;
    cout << "\n===== SIMULATION RESULTS =====\n";
    cout << "Total Accesses: " << totalAccesses << endl;
    cout << "TLB Hits:       " << tlbHits << endl;
    cout << "Page Hits:      " << hits - tlbHits << endl;
    cout << "Page Faults:    " << faults << endl;
    cout << "Disk Writes:    " << diskWrites << endl;

    double hitRate = (double)hits / totalAccesses;
    double EAT = (double)totalTime / totalAccesses;

    cout << "Hit Rate:       " << hitRate * 100 << "%\n";
    cout << "Avg EAT:        " << EAT << " ns\n";
}