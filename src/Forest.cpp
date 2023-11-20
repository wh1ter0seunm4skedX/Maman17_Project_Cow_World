/**
* The Forest class represents a 3D forest in a virtual environment.
* A forest consists of a number of Tree objects placed at random positions.
* Each Tree object in the Forest is drawn and managed by the Forest object itself.
*
* The Forest class provides functionality to create a forest with a specified 
* number of trees, or a default of three trees if no number is specified.
*/
#include "Forest.h"
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <GL/glut.h>

/**
* The default constructor initializes a Forest object with a default of 3 trees.
* It initializes a random seed and generates the positions of each tree within the forest.
*/
Forest::Forest() : Forest(3) {}  // Default to 3 trees
/**
* This constructor initializes a Forest object with the specified number of trees.
* It initializes a random seed and generates the positions of each tree within the forest.
*/
Forest::Forest(const int num_trees) {
    // Initialize random seed
    std::srand(std::time(0));

    // Create trees and their positions
    for (int i = 0; i < num_trees; ++i) {
        trees.push_back(Tree());
        xPos.push_back(3 + std::rand() % 5);
        zPos.push_back(-6 + std::rand() % 5);
    }
}

/**
*
* This method draws all the trees in the forest at their respective positions.
* It uses OpenGL to handle the transformations and drawing of each Tree object.
*/
void Forest::draw() {
    for (int i = 0; i < trees.size(); ++i) {
        glPushMatrix();
        glTranslatef(xPos[i], 0.0f, zPos[i]);
        trees[i].draw();
        glPopMatrix();
    }
}
