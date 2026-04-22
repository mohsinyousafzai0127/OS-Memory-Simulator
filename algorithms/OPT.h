#pragma once
#include "Replacement.h"
#include <unordered_map>
#include <queue>
#include <vector>

class OPT : public Replacement {
private:
    std::unordered_map<int, std::queue<int>> futureUse;
    std::vector<int>* currentFrames;
    int currentIndex;

public:
    OPT(std::unordered_map<int, std::queue<int>> future,
        std::vector<int>* frames)
        : futureUse(future), currentFrames(frames), currentIndex(0) {}

    void setIndex(int idx) {
        currentIndex = idx;
    }

    void access(int vpn) override {
        if (!futureUse[vpn].empty())
            futureUse[vpn].pop();
    }

    int evict() override {
        int victim = -1;
        int farthest = -1;

        for (int vpn : *currentFrames) {
            if (futureUse[vpn].empty())
                return vpn;

            int nextUse = futureUse[vpn].front();
            if (nextUse > farthest) {
                farthest = nextUse;
                victim = vpn;
            }
        }
        return victim;
    }
};