#pragma once
#include <vector>

class Replacement {
public:
    virtual void access(int vpn) = 0;   // when page accessed
    virtual int evict() = 0;            // choose victim
    virtual ~Replacement() {}
};