//
// This file contains the implementation of the Camera class.
// The Camera class is used to control the viewpoint from which the scene is rendered in OpenGL.
//
#include "Camera.h"
#include <GL/glut.h> 

// The constructor initializes a new instance of the Camera class.
// It sets the camera's initial position and target viewing point using initializer lists.
// The position is a point in 3D space where the camera is located.
// The target is a point in 3D space that the camera is looking at.
Camera::Camera() :camera_position{ 8.0f, 5.0f, 16.0f },
				  camera_target{ -2.0f, 0.0f, 0.0f } {};

// You can add a method in your Camera class to update the view matrix
void Camera::UpdateView() {
	// Assuming up vector is constant and is (0, 1, 0)
	GLfloat up[3] = {0.0f, 1.0f, 0.0f};

	// set the matrix mode to modelview
	glMatrixMode(GL_MODELVIEW);

	// load identity matrix
	glLoadIdentity();

	// gluLookAt sets the matrix based on eye position, center position, and up direction
	gluLookAt(camera_position[0], camera_position[1], camera_position[2],  // camera position
			  camera_target[0], camera_target[1], camera_target[2],        // lookat position (the cow)
			  up[0], up[1], up[2]);                   // up vector
}

// And also add methods to update camera's position and target
void Camera::SetPosition(float x, float y, float z) {
	camera_position[0] = x;
	camera_position[1] = y;
	camera_position[2] = z;
}

void Camera::SetTarget(float x, float y, float z) {
	camera_target[0] = x;
	camera_target[1] = y;
	camera_target[2] = z;
}
