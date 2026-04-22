#include "TLB.h"

TLB::TLB(int size) : capacity(size) {}

int TLB::lookup(int vpn) {
    for (auto &e : entries) {
        if (e.vpn == vpn)
            return e.frame;
    }
    return -1;
}

void TLB::insert(int vpn, int frame) {
    // Remove if already exists
    for (auto it = entries.begin(); it != entries.end(); ++it) {
        if (it->vpn == vpn) {
            entries.erase(it);
            break;
        }
    }

    // FIFO eviction
    if (entries.size() >= capacity) {
        entries.erase(entries.begin());
    }

    entries.push_back({vpn, frame});
}

void TLB::invalidate(int vpn) {
    for (auto it = entries.begin(); it != entries.end(); ++it) {
        if (it->vpn == vpn) {
            entries.erase(it);
            return;
        }
    }
}