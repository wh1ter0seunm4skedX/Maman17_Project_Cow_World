#pragma once
#include "Tree.h"
#include <vector>

class Forest {
public:
    Forest();
    Forest(int num_trees);
    void draw();

private:
    std::vector<Tree> trees;
    std::vector<float> xPos;
    std::vector<float> zPos;
};

