// This file contains the implementation of the Farmhouse class methods, as well as the standalone function renderBitmapString.
// The Farmhouse class is responsible for creating the visual representation of a farmhouse using OpenGL.
// 
// Includes necessary headers from the OpenGL library and the Farmhouse class definition header file.

#include <GL/glut.h>
#include "Farmhouse.h"

// This is a member function of the Farmhouse class that is responsible for drawing a 3D representation of a farmhouse.
// The method sets up the necessary transformations, then draws each part of the farmhouse in turn:
// - Main structure
// - Roof
// - Chimney
// - Door
// - Windows
// Each part of the farmhouse is drawn with its appropriate color and transformation.
// The method also ensures the transformations applied to each part don't affect the others by using glPushMatrix and glPopMatrix.

void Farmhouse::draw() {
    glPushMatrix();

    glTranslatef(5.0f, 2.3f, -10.0f);
    glScalef(5.0f, 5.0f, 5.0f);

    // Draw main structure
    GLfloat main_structure_color[] = { 0.8f, 0.8f, 0.5f, 1.0f }; 
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, main_structure_color);
    glutSolidCube(1.0f);

    // Draw roof
    GLfloat roof_color[] = { 0.5f, 0.25f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, roof_color);
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glScalef(1.2f, 0.5f, 1.0f);
    glutSolidCone(1.0f, 1.0f, 4, 2);
    glPopMatrix();

    // Draw chimney
    GLfloat chimney_color[] = { 0.5f, 0.25f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, chimney_color);
    glPushMatrix();
    glTranslatef(0.35f, 0.4f, 0.0f);
    glScalef(0.1f, 0.4f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Draw door
    GLfloat door_color[] = { 0.4f, 0.2f, 0.1f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, door_color);
    glPushMatrix();
    glTranslatef(0.0f, -0.25f, 0.5f);
    glScalef(0.25f, 0.5f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Draw windows
    GLfloat windows_color[] = { 0.75f, 0.75f, 0.95f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, windows_color);
    for (int i = -1; i <= 1; i += 2) {
        glPushMatrix();
        glTranslatef(i * 0.4f, 0.2f, 0.5f);
        glScalef(0.2f, 0.2f, 0.1f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    glPopMatrix();
}


