#include "FrameManager.h"

FrameManager::FrameManager(int numFrames) {
    for (int i = numFrames - 1; i >= 0; i--)
        freeFrames.push(i);
}

bool FrameManager::hasFreeFrame() {
    return !freeFrames.empty();
}

int FrameManager::allocate() {
    int f = freeFrames.top();
    freeFrames.pop();
    return f;
}