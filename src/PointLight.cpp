/**
 * The PointLight class represents a point light source in a 3D virtual environment 
 * using the OpenGL library. A point light source emits light in all directions 
 * from a specific position in space. It defines the color, position, and speed of movement
 * of the point light source and provides methods to update its position over time, 
 * add the light to the scene, draw a visual representation of the light source, 
 * and enable or disable the light.
 */

#include "PointLight.h"
#include <cmath> // For cos function
/**
 * The default constructor initializes the PointLight object with a specific color, 
 * position, speed of movement along the x-axis, and sets the initial time to zero.
 */
PointLight::PointLight() : color{ 0.691f, 0.653f, 0.254f , 1.0f },
						   position{ -5.0f, 5.0f, 0.0f , 1.0f },
						   speed{ 0.05f },  // speed of movement along the x-axis
						   time{ 0.0f } {}  // time since the light was created

/**
 * This method updates the position of the point light source based on the elapsed time. 
 * The light source moves back and forth along the x-axis.
 */
void PointLight::update(float deltaTime) {
	time += deltaTime;
	position[0] = 5.0f * cos(speed * time);  // Move back and forth along the x-axis
}

/**
 * This method adds the point light source to the scene using OpenGL. 
 * It sets the diffuse and specular color of the light and its position.
 * The method also sets the spot cutoff to 180, resulting in uniform light distribution.
 */
void PointLight::addLight() {
	if (!glIsEnabled(GL_LIGHT0))
		return;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, color);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	//The initial spot cutoff is 180, resulting in uniform light distribution.
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0f);
}
/**
 * This method draws a visual representation of the point light source as a sphere 
 * with the color of the light source.
 */
void PointLight::draw()
{
	if (!glIsEnabled(GL_LIGHT0))
		return;
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor4fv(color);
	glutSolidSphere(0.2, 100, 100);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
/**
 * This method disables the point light source.
 */
void PointLight::disable()
{
	glDisable(GL_LIGHT0);
}
/**
 * This method enables the point light source.
 */
void PointLight::enable()
{
	glEnable(GL_LIGHT0);
}