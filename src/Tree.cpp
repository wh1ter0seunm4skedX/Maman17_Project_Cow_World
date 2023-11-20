/**
 * The Tree class represents a tree in a 3D virtual environment using OpenGL.
 * It provides a method to draw the tree using recursion for the branches. The leaves 
 * are represented by green spheres and the branches are represented by cylinders.
 */

#include <GL/glut.h>
#include "Tree.h"

/**
 * This method draws the entire tree. It initiates the drawing process 
 * by rotating the initial drawing axis and calling the drawBranch method 
 * to recursively draw the branches of the tree.
 */
void Tree::draw() {
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    drawBranch(3);
    glPopMatrix();
}

/**
 * This method draws a single branch of the tree. If the depth is 0, a leaf is drawn as a green sphere.
 * Otherwise, a cylinder is drawn to represent the branch, and the method is recursively called to draw
 * three smaller branches off the end of the current branch.
 * The branch thickness decreases as the depth increases, and the branches diverge at 60-degree angles.
 */
void Tree::drawBranch(int depth) {
    GLUquadric* quadratic = gluNewQuadric();

    if (depth == 0) {
        glColor3f(0.0, 1.0, 0.0); // Green
        glutSolidSphere(0.2, 10, 10);
        glColor3f(0.65, 0.16, 0.16); // Brown
    }
    else {
        gluCylinder(quadratic, 0.1, 0.08, 0.5, 10, 10);
        glTranslatef(0, 0, 0.5);

        for (int i = 0; i < 3; ++i) {
            glPushMatrix();
            glRotatef(60 * (i - 1), 0, 1, 0);
            glRotatef(30, 1, 0, 0);
            drawBranch(depth - 1);
            glPopMatrix();
        }
    }

    gluDeleteQuadric(quadratic);
}
