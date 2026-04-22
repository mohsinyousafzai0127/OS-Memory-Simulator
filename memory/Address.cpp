#include "Address.h"

int Address::getVPN(unsigned int addr, int offsetBits) {
    return addr >> offsetBits;
}

int Address::getOffset(unsigned int addr, int pageSize) {
    return addr & (pageSize - 1);
}