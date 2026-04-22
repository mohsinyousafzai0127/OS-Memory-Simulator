#include "Config.h"
#include <fstream>
#include <string>
#include <cmath>

Config Config::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string json, line;

    while (getline(file, line))
        json += line;

    auto getVal = [&](std::string key) {
        size_t pos = json.find("\"" + key + "\"");
        pos = json.find(":", pos);
        size_t end = json.find(",", pos);
        return stoi(json.substr(pos + 1, end - pos));
    };

    Config c;
    c.RAM_SIZE = getVal("RAM_SIZE");
    c.PAGE_SIZE = getVal("PAGE_SIZE");
    c.TLB_SIZE = getVal("TLB_SIZE");
    c.TLB_LATENCY = getVal("TLB_LATENCY");
    c.RAM_LATENCY = getVal("RAM_LATENCY");
    c.DISK_LATENCY = getVal("DISK_LATENCY");

    c.numFrames = c.RAM_SIZE / c.PAGE_SIZE;
    c.offsetBits = log2(c.PAGE_SIZE);

    return c;
}