#pragma once
#include <GL/freeglut.h>
#include <functional>

/*
The Cow object, renders the cow and exposes the cow controls to the ui.
*/
class Cow
{
public:
	Cow();
	GLfloat local_coords[16];	//local coordinate system transformation matrix
	GLfloat head_horizontal_angle;
	GLfloat head_vertical_angle;
	GLfloat tail_horizontal_angle;
	GLfloat tail_vertical_angle;
	std::function<void()> next_move;
	void update_position(float new_x, float new_y, float new_z);

	bool is_moving;
	float position[3];

	void init();
	void draw();
	~Cow() = default;
private:
	//update constant animation for tail wiggle and legs movement
	void update_constant_movement();

	GLfloat tail_wiggle_angle;
	bool tail_wiggle_direction_left;
	GLfloat legs_angle;
	bool legs_movement_direction_forward;
};
