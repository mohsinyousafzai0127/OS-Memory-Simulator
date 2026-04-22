#pragma once
#include <unordered_map>

struct PTE {
    bool valid = false;
    bool dirty = false;
    int frame = -1;
};

class PageTable {
private:
    std::unordered_map<int, PTE> table;

public:
    bool isValid(int vpn);
    PTE& get(int vpn);
    void invalidate(int vpn);
};