#pragma once

class Address {
public:
    static int getVPN(unsigned int addr, int offsetBits);
    static int getOffset(unsigned int addr, int pageSize);
};