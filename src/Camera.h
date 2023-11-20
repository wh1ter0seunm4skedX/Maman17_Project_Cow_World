#pragma once
#include <GL/freeglut.h>

/*
The Camera controlling the external view point.
*/
class Camera
{
public:
	Camera();
	GLfloat camera_position[3];
	GLfloat camera_target[3];
	void UpdateView();
	void SetPosition(float x, float y, float z);
	void SetTarget(float x, float y, float z);

	~Camera() = default;
};
