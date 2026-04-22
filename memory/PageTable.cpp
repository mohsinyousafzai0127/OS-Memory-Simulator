#include "PageTable.h"

bool PageTable::isValid(int vpn) {
    return table[vpn].valid;
}

PTE& PageTable::get(int vpn) {
    return table[vpn];
}

void PageTable::invalidate(int vpn) {
    table[vpn].valid = false;
}