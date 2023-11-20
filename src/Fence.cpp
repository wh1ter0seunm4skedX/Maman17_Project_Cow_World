/**
* Class: Fence
 *
 * Description:
 * The Fence class represents a 3D fence in a virtual environment.
 * The fence consists of posts and planks which are evenly distributed
 * to form a rectangular fence structure. The fence is brown in color.
 *
 * A Fence object is responsible for providing a method to draw itself,
 * given a list of indexes representing sections of the fence to draw.
 */

#include "Fence.h"
/**
 * Default Constructor: Fence::Fence()
 *
 * Description:
 * The default constructor initializes a Fence object.
 */
Fence::Fence() {}

/**
* This method draws the sections of the fence as specified by the indices 
* in the provided list. It uses OpenGL to draw cylinders and cubes for the 
* posts and planks respectively.
**/

void Fence::draw(std::vector<int> fenceIndexes) {
    for (int i : fenceIndexes) {
        glColor3f(0.55f, 0.27f, 0.075f);  // Brown color for fence

        // Draw the fence posts and planks on each side of the fence
        for (int side = 0; side < 2; ++side) {
            // Set the Z value depending on the side of the fence
            int z = side == 0 ? -50 : 50;

            for (int x = -50; x <= 50; ++x) {
                // Draw fence posts
                glPushMatrix();
                glTranslatef(x, 0, z);
                glRotatef(-90, 1, 0, 0);
                glutSolidCylinder(0.1, 1, 20, 20);
                glPopMatrix();

                // Draw fence planks
                if (x != 50) {
                    for (float y = 0.2; y <= 0.8; y += 0.3) {
                        glPushMatrix();
                        glTranslatef(x + 0.5, y, z);
                        glScalef(1, 0.1, 0.05);
                        glutSolidCube(1);
                        glPopMatrix();
                    }
                }
            }
        }

        // Draw the fence posts and planks on the remaining sides
        for (int side = 0; side < 2; ++side) {
            int x = side == 0 ? -50 : 50;

            for (int z = -50; z <= 50; ++z) {
                glPushMatrix();
                glTranslatef(x, 0, z);
                glRotatef(-90, 1, 0, 0);
                glutSolidCylinder(0.1, 1, 20, 20);
                glPopMatrix();

                if (z != 50) {
                    for (float y = 0.2; y <= 0.8; y += 0.3) {
                        glPushMatrix();
                        glTranslatef(x, y, z + 0.5);
                        glScalef(0.05, 0.1, 1);
                        glutSolidCube(1);
                        glPopMatrix();
                    }
                }
            }
        }
    }
}
