/**
* The Ground class represents the ground surface in a 3D virtual environment.
 * The ground surface is a plane and it's characterized by its start and end positions 
 * along the X and Z axes. The ground has a defined color (default to dark green)
 * and materials properties.
 * 
 * The Ground class provides functionality to draw the ground surface using OpenGL.
*/
#include "Ground.h"

Ground::Ground() : start_x(-50), start_z(-50), end_x(50), end_z(50),
color{ 0.0f, 0.39f, 0.0f, 1.0f } {} // Dark green color
/**
 * This method draws the ground using OpenGL. The ground is drawn as a grid of quadrilaterals,
 * each quad has a material assigned (specular, shininess, ambient and diffuse components) 
 * that determines how it reflects light. This creates a more realistic representation of a 
 * ground surface under different lighting conditions.
 */
void Ground::draw()
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3d(0, 1, 0);
    constexpr GLfloat specular[] = { 1.0f, 1.0f, 1.0f };
    constexpr GLfloat shininess = 128.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    for (int x = start_x; x < end_x; x++) {
        for (int z = start_z; z < end_z; z++) {
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
            glVertex3d(x, 0, z);
            glVertex3d(x + 1, 0, z);
            glVertex3d(x + 1, 0, z + 1);
            glVertex3d(x, 0, z + 1);
        }
    }

    glEnd();
    glPopMatrix();
}
