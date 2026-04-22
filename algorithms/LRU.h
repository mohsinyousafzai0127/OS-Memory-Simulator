#pragma once
#include "Replacement.h"
#include <list>
#include <unordered_map>

class LRU : public Replacement {
private:
    std::list<int> lruList;
    std::unordered_map<int, std::list<int>::iterator> lruMap;

public:
    void access(int vpn) override {
        if (lruMap.count(vpn)) {
            lruList.erase(lruMap[vpn]);
        }
        lruList.push_front(vpn);
        lruMap[vpn] = lruList.begin();
    }

    int evict() override {
        int victim = lruList.back();
        lruList.pop_back();
        lruMap.erase(victim);
        return victim;
    }
};