#pragma once
#include <vector>
#include <GL/glut.h>

class Wheat {
public:
    Wheat(GLfloat x, GLfloat y, GLfloat z);

    void draw();
    static void createField(std::vector<Wheat>& field);

private:
    GLfloat position[3];
};

