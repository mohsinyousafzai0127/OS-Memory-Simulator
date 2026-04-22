#pragma once
#include <string>

struct Config {
    int RAM_SIZE, PAGE_SIZE, TLB_SIZE;
    int TLB_LATENCY, RAM_LATENCY, DISK_LATENCY;

    int numFrames;
    int offsetBits;

    static Config loadFromFile(const std::string& filename);
};