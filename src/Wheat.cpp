/**
 * The Wheat class represents a stalk of wheat in a 3D graphics environment using OpenGL.
 * It provides a constructor to set the initial position of the wheat stalk in 3D space,
 * and a draw method to render the wheat stalk. The wheat stalk is rendered as a single line
 * segment with a golden color characteristic of ripe wheat.
 */

#include "Wheat.h"

/**
 * This is the constructor for the Wheat class. It initializes a wheat stalk's position 
 * in 3D space to the given parameters.
 */
Wheat::Wheat(GLfloat x, GLfloat y, GLfloat z) {
    position[0] = x;
    position[1] = y;
    position[2] = z;
}

/**
 * This method draws a wheat stalk in 3D space. The wheat stalk is represented as a vertical line 
 * segment of a certain length. The base of the wheat stalk is located at the position specified 
 * in the constructor, and the wheat stalk extends upwards from this point. The wheat stalk is 
 * colored using the wheatColor array to appear golden.
 */
void Wheat::draw() {
    glPushMatrix();

    constexpr GLfloat wheat_color[] = { 0.9f, 0.7f, 0.1f, 1.0f }; // Wheat color
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wheat_color);

    glTranslatef(position[0], position[1], position[2]);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f); // The y coordinate can be changed to control the height of the wheat
    glEnd();

    glPopMatrix();
}

// Create a static method to generate a field of wheat
void Wheat::createField(std::vector<Wheat>& field) {
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 50; ++j) {
            field.push_back(Wheat(i, 0, j));
            field.push_back(Wheat(-i, 0, -j));
        }
    }
}