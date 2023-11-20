#pragma once
#include <GL/freeglut.h>

class Ground
{
public:
    Ground();
    void draw();
    ~Ground() = default;
private:
    int start_x, start_z, end_x, end_z;
    GLfloat color[4];
};
