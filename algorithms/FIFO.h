#pragma once
#include "Replacement.h"
#include <queue>
#include <unordered_set>

class FIFO : public Replacement {
private:
    std::queue<int> q;
    std::unordered_set<int> inQueue; // Tracks what is currently in the FIFO queue

public:
    void access(int vpn) override {
        // Only add to the FIFO queue if it's not already being tracked (i.e., on a Fault)
        if (inQueue.find(vpn) == inQueue.end()) {
            q.push(vpn);
            inQueue.insert(vpn);
        }
    }

    int evict() override {
        if (q.empty()) return -1;
        int victim = q.front();
        q.pop();
        inQueue.erase(victim); // Remove from tracking
        return victim;
    }
};