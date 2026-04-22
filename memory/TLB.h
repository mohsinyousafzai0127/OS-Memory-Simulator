#pragma once
#include <vector>

struct TLBEntry {
    int vpn;
    int frame;
};

class TLB {
private:
    int capacity;
    std::vector<TLBEntry> entries;

public:
    TLB(int size);

    int lookup(int vpn);           // return frame or -1
    void insert(int vpn, int frame);
    void invalidate(int vpn);      
};