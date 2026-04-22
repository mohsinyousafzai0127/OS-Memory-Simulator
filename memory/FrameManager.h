#pragma once
#include <stack>

class FrameManager {
private:
    std::stack<int> freeFrames;

public:
    FrameManager(int numFrames);
    bool hasFreeFrame();
    int allocate();
};