#pragma once
#include <GL/freeglut.h>

/*
PointLight is light source with uniform light distribution.
*/
class PointLight
{
public:
	GLfloat color[4];
	GLfloat position[4];
	GLfloat speed;
	GLfloat time;
	
	PointLight();
	void PointLight::update(float deltaTime);
	void addLight();
	void draw();
	void disable();
	void enable();
	~PointLight() = default;
};

