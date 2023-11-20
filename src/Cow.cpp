// This file defines the Cow class methods and behavior.
// Each Cow object represents a cow in the OpenGL scene, with a specified behavior and
// properties such as its current position, head and tail orientation, and leg movement.

#include "Cow.h"
#include <GL/freeglut.h>
#include <iostream>

// A cow can be initialized using its default constructor Cow(), which sets up the initial
// orientation for its head, tail, and legs. Furthermore, the cow's orientation and position
// can be updated through the updatePosition() method.

Cow::Cow() : head_horizontal_angle(0.0f),
	head_vertical_angle(10.0f),
	tail_horizontal_angle(0.0f),
	tail_vertical_angle(-10.0f),
	tail_wiggle_angle(0.0f),
	tail_wiggle_direction_left(true),
	legs_angle(0.0f),
	legs_movement_direction_forward(true),
	next_move(nullptr),
	is_moving(false)
{};

// The init() method is used to set up the local coordinates for the cow in the OpenGL scene.
// It aligns the cow's initial position and orientation according to the scene's setup.

void Cow::init() {
    GLfloat view_model_matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, view_model_matrix);
	glLoadIdentity();

	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(-0.5, 3.5f * 0.30f, -2.8f);

	glGetFloatv(GL_MODELVIEW_MATRIX, local_coords);
	glLoadMatrixf(view_model_matrix);
}

// The updatePosition(...) updates the position of the cow within the virtual environment. 
// If the proposed new position falls within either a lake or a farmhouse, 
// the method will prevent the move and notify the user.
// Otherwise, it updates the cow's position to the new coordinates and sets 
// the cow's isMoving flag to true, indicating that the cow is now in motion.

void Cow::update_position(float new_x, float new_y, float new_z) {
	// Check if new position is inside the lake
	if (new_x > 0 && new_x < -50 && new_z > 0 && new_z < 50) {
		std::cout << "Cannot move into the lake!" << std::endl;
		return;
	}
    
	// Check if new position is inside the farmhouse
	// NOTE: This is a simplification. Adjust the numbers as necessary.
	if (new_x > 5.0f && new_x < 10.0f && new_y > 2.3f && new_y < 7.3f && new_z > -10.0f && new_z < -5.0f) {
		std::cout << "Cannot move into the farmhouse!" << std::endl;
		return;
	}
    
	// If not inside lake or farmhouse, update position
	this->position[0] = new_x;
	this->position[1] = new_y;
	this->position[2] = new_z;
	is_moving = true; // the cow is now moving
}

// The draw() method uses OpenGL calls to draw the cow in the scene. It uses different
// primitives to represent the different parts of the cow such as head, legs, tail, etc.
// Each part is transformed to the appropriate position and orientation and then rendered.
// The material properties and color for each part are also set during rendering.

void Cow::draw() {
	
	update_constant_movement();	
	glPushMatrix();
	// in Cow.h
	constexpr GLfloat color[4] = { 0.92f, 0.814f, 0.382f, 1.0f };
	constexpr GLfloat white_color[3] = { 1.0f, 1.0f, 1.0f };
	constexpr GLfloat black_color[3] = { 0.0f, 0.0f, 0.0f };
	constexpr GLfloat pink_color[3] = { 1.0f, 0.75f, 0.8f };

	glColor4fv(color);

	constexpr GLfloat cow_specular[] = { 0.1f, 0.1f, 0.1f };
	constexpr GLfloat cow_shininess = 0.1f;

	glMaterialfv(GL_FRONT, GL_SPECULAR, cow_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, cow_shininess);
	glMaterialf(GL_FRONT, GL_EMISSION, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

	// torso
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white_color);
	glScalef(2.0f * 0.3f, 2.0f * 0.3f, 4.0f * 0.3f);
	glutSolidSphere(1, 30, 30);
	glBindTexture(GL_TEXTURE_2D, 0);  // unbind the texture
	glPopMatrix();


	//legs
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black_color);
	glRotatef(legs_angle, 1, 0, 0);
	glTranslated(-1 * 0.3, -2.5 * 0.3, -2 * 0.3);
	glScalef(0.5f * 0.3f, 2.0f * 0.3f, 0.5f * 0.3f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-legs_angle, 1, 0, 0);
	glTranslated(0.3f, -2.5f * 0.3f, -0.6);
	glScalef(0.5f * 0.3f, 0.6f, 0.5f * 0.3f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(legs_angle, 1, 0, 0);
	glTranslated(0.3f, -2.5f * 0.3f, 2.0 * 0.3f);
	glScalef(0.5f * 0.3f, 2.0f * 0.3f, 0.5f * 0.3f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-legs_angle, 1, 0, 0);
	glTranslated(-0.3f, -2.5f * 0.3f, 0.6);
	glScalef(0.5f * 0.3f, 2.0f * 0.3f, 0.5f * 0.3f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();

	//tail
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white_color);

	glTranslated(0.0f, 0.0f, -3.8f * 0.3f);
	glRotatef(-30, 1, 0, 0);
	glRotatef(tail_vertical_angle, 1, 0, 0);
	glRotatef(tail_horizontal_angle, 0, 1, 0);
	glRotatef(tail_wiggle_angle, 0, 1, 0);
	glScalef(0.3f * 0.3f, 0.3f * 0.3f, 2.5f * 0.3f); // Modify these values as necessary

	glutSolidSphere(1, 30, 30);

	// tail end (black ball)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black_color); // set color to black
	glTranslatef(0.0f, 0.0f, -1.0f); // adjust this as necessary
	glScalef(1.0f / (0.3f * 0.3f), 1.0f / (0.3f * 0.3f), 1.0f / (2.5f * 0.3f)); // reset the scaling
	glutSolidSphere(0.2f, 30, 30); // black ball at the end of the tail, adjust size as necessary
	glPopMatrix();
	
	//head rotation
	glPushMatrix();
	glRotatef(head_vertical_angle, 1, 0, 0);
	glRotatef(head_horizontal_angle, 0, 1, 0);

	//head
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white_color);

	glTranslated(0.0f, 2.5f * 0.3f, 3.0f * 0.3f);
	glScalef(2.0f * 0.3f, 1.5f * 0.3f, 2.0f * 0.3f); // Made the head longer and wider
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	
	//nose
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pink_color);

	glTranslated(0.0f, 2.0f * 0.3f, 4.0f * 0.3f); // Slightly lowered and extended the nose
	glScalef(1.0f * 0.3f, 0.7f * 0.3f, 2.0f * 0.3f); // Made the nose broader and longer
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	
	//ears
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black_color);
	glTranslated(-1.2f * 0.3f, 3.0f * 0.3f, 2.6f * 0.3f); // Positioned the ears more to the side and lower
	glScalef(0.7f * 0.3f, 0.5f * 0.3f, 0.7f * 0.3f); // Made the ears larger and longer
	glutSolidSphere(1, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.2f * 0.3f, 3.0f * 0.3f, 2.6f * 0.3f); // Positioned the ears more to the side and lower
	glScalef(0.7f * 0.3f, 0.5f * 0.3f, 0.7f * 0.3f); // Made the ears larger and longer
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	
	constexpr GLfloat eyes_specular[] = { 0.4f, 0.4f, 0.4f };
	constexpr GLfloat eyes_shininess = 1.0f;

	//eyes
	glColor4fv(black_color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, eyes_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, eyes_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black_color);

	glPushMatrix();
	glTranslated(1.5f * 0.3f, 3.0f * 0.3f, 4.4f * 0.3f);
	glScalef(0.25f * 0.3f, 0.25f * 0.3f, 0.25f * 0.3f);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1.5f * 0.3f, 3.0f * 0.3f, 4.4f  * 0.3f);
	glScalef(0.25f * 0.3f, 0.25f * 0.3f, 0.25f * 0.3f);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

//The updateConstantMovement() method is used to animate the cow, providing a sense of
// movement to its tail and legs.

void Cow::update_constant_movement() {
	if (tail_wiggle_angle > 8 || tail_wiggle_angle < -8)
	{
		tail_wiggle_direction_left = !tail_wiggle_direction_left;
	}
	if (tail_wiggle_direction_left)
	{
		tail_wiggle_angle += 0.3f;
	}
	else {
		tail_wiggle_angle -= 0.3f;
	}

	// Only adjust the legs angle if the cow is moving
	if (is_moving) {
		if (legs_angle > 20 || legs_angle < -20)
		{
			legs_movement_direction_forward = !legs_movement_direction_forward;
		}
		if (legs_movement_direction_forward)
		{
			legs_angle += 6.0;
		}
		else {
			legs_angle -= 6.0;
		}
		is_moving = false; // the cow is now moving

	}
}
