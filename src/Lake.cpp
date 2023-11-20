/**
 * The Lake class represents a water body (lake) in a 3D virtual environment.
 * The lake surface is defined as a plane that has a specific start and end points 
 * on the X and Z axes, and a constant Y-coordinate for the water level.
 * The lake has a defined color (semi-transparent blue), allowing for the visualization 
 * of a water-like appearance.
 *
 * The Lake class provides functionality to draw the lake and its border using OpenGL.
 */


#include "Lake.h"
/**
 * The default constructor initializes the Lake object with a specific starting and ending points
 * on the X and Z axes, and sets its color to semi-transparent blue.
 */
Lake::Lake() :start_x(0), start_z(50), end_x(-50), end_z(0),
    y(0.1), color{ 0.0f, 0.4f, 1.0f, 0.7f } {} // Semi-transparent blue color

/**
 * This method draws the lake using OpenGL. It also enables blending for semi-transparency effect,
 * and sets the material color to blue. The lake is drawn as a quadrilateral (quad) defined 
 * by the start and end points.
 *
 * After the lake is drawn, blending is disabled and the border of the lake is drawn by 
 * calling the drawBorder method.
 */
void Lake::draw() {
    glPushMatrix();
    glEnable(GL_BLEND); // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set blending function

    constexpr GLfloat blue[] = {0.0f, 0.0f, 1.0f, 1.0f}; // Blue color
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue); // Set the material color to blue

    glBegin(GL_QUADS);
    glVertex3f(start_x, y, start_z);
    glVertex3f(end_x, y, start_z);
    glVertex3f(end_x, y, end_z);
    glVertex3f(start_x, y, end_z);
    glEnd();

    glDisable(GL_BLEND); // Disable blending
    glPopMatrix();

    drawBorder();
}
/**
 * This method draws the border of the lake using OpenGL. The border is drawn as a line loop
 * with a defined color (brown) and a set line width.
 */
void Lake::drawBorder() {
    glPushMatrix();

    constexpr GLfloat brown[] = {0.6f, 0.3f, 0.0f, 1.0f}; // Brown color
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown); // Set the material color to brown

    glLineWidth(3.0); // Set line width

    glBegin(GL_LINE_LOOP);
    glVertex3f(start_x, y, start_z);
    glVertex3f(end_x, y, start_z);
    glVertex3f(end_x, y, end_z);
    glVertex3f(start_x, y, end_z);
    glEnd();

    glPopMatrix();
}
