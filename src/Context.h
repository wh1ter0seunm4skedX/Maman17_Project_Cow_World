// Context.cpp
//
// This file contains the implementation of the Context class. The Context class serves as a container
// for all objects that are to be rendered in the scene. It also contains a camera object to capture the scene,
// and settings like global ambient light and cow view toggle.
// The contained objects include a ground plane, a cow, a point light, a spotlight, a fence, a forest, a farmhouse,
// a lake, and a wheat field. All of these objects have their respective classes and functionalities.
//
// Includes the necessary header files for scene objects and OpenGL.
#pragma once
#include <vector>
#include "Cow.h"
#include "Ground.h"
#include "PointLight.h"
#include "Spotlight.h"
#include "Camera.h"
#include "Fence.h"
#include "Forest.h"
#include "Farmhouse.h"
#include "Wheat.h"
#include "Lake.h"

/*
Context class - container for all objects in the scene.
*/
class Context {
public:
	GLfloat globalAmbient = 0.3f; // Global ambient light intensity
	int isCowView = 0; // Flag to check if the camera is in cow's perspective
	Camera camera; // Camera object to capture the scene
	Ground ground; // Ground object represents the terrain
	Cow cow; // Cow object 
	PointLight pointlight; // Point light source in the scene
	SpotLight spotlight; // Spotlight source in the scene
	Fence fence; // Fence object
	Forest forest; // Forest object
	Farmhouse farmhouse; // Farmhouse object
	Lake lake; // Lake object
	std::vector<Wheat> wheatField; // Vector of Wheat objects representing a field of wheat
};
