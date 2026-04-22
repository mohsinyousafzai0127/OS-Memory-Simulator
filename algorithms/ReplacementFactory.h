#pragma once
#include "FIFO.h"
#include "LRU.h"
#include "OPT.h"
#include <string>

class ReplacementFactory {
public:
    static Replacement* create(
        const std::string& type,
        std::unordered_map<int, std::queue<int>> futureUse = {},
        std::vector<int>* frames = nullptr
    ) {
        if (type == "FIFO") return new FIFO();
        if (type == "LRU") return new LRU();
        if (type == "OPT") return new OPT(futureUse, frames);

        return nullptr;
    }
};