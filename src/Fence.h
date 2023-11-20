#pragma once
#include <vector>
#include <GL/freeglut.h>

class Fence {
public:
    Fence();
    void draw(std::vector<int> fenceIndexes);
};
