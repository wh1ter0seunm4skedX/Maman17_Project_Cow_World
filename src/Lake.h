#pragma once
#include <GL/glut.h>

class Lake {
public:
    GLfloat start_x, start_z, end_x, end_z; // Coordinates for the lake
    GLfloat y; // The height of the lake
    GLfloat color[4]; // The color of the lake

    Lake();
    void draw();
    void Lake::drawBorder();

};