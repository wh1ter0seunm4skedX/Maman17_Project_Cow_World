/**
* This program uses OpenGL along with GLUT and ImGui for drawing 3D graphics and creating a simple
* GUI, respectively. The scene comprises several components such as a cow, a farmhouse, a lake,
* a forest, a wheat field, and a dynamic lighting setup. The user can interact with the cow and the 
* camera using the keyboard. 
*/

#include <windows.h>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_freeglut.h"
#include "imgui_impl_opengl2.h"
#include <GL\freeglut.h>
#include "Context.h"
#include "Menu.h" 

using namespace std;

//single point of access to all rendered objects
Context context;
Menu menu(context); // make menu global

/*
* This function checks if the cow is colliding with the farmhouse or the lake 
* while moving.
*/
bool checkCollision(float x, float z) {
	// Define farmhouse and lake positions
	float farmhouseX = 5.0f, farmhouseZ = -10.0f;
	float lakeStartX = 0.0f, lakeStartZ = 50.0f;
	float lakeEndX = -50.0f, lakeEndZ = 0.0f;

	// Define collision distances
	float farmhouseCollisionDistance = 5.0f; // Based on scaling of the farmhouse

	// Check farmhouse collision
	float dx = x - farmhouseX, dz = z - farmhouseZ;
	if (sqrt(dx * dx + dz * dz) < farmhouseCollisionDistance) {
		return true;
	}

	// Check lake collision
	if ((x > lakeEndX && x < lakeStartX) && (z > lakeEndZ && z < lakeStartZ)) {
		return true;
	}

	return false;
}
/*
* Keyboard, normalKeys: These functions capture the keyboard inputs for controlling the cow 
* and the camera. The cow can be moved in all four directions using the arrow keys, while the camera 
* can be moved up, down, left, or right using the keys 'w', 's', 'a', 'd'.
*/

void keyboard(int key, int, int) {
	GLfloat viewModelMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, viewModelMatrix);
	glLoadMatrixf(context.cow.local_coords);

	std::function<void()> nextMove;

	switch (key) {
	case GLUT_KEY_LEFT:
		nextMove = []() { glRotatef(7, 0, 1, 0); };
		break;
	case GLUT_KEY_RIGHT:
		nextMove = []() { glRotatef(-7, 0, 1, 0); };
		break;
	case GLUT_KEY_UP:
		nextMove = []() { glTranslated(0, 0, 0.2); };
		break;
	case GLUT_KEY_DOWN:
		nextMove = []() { glTranslated(0, 0, -0.2); };
		break;
	default:
		// No valid key press detected, so the cow isn't moving.
		context.cow.is_moving = false;
		return;
	}

	context.cow.is_moving = true;  // The cow is moving now

	// apply the potential movement
	nextMove();

	// check if there will be a collision
	GLfloat nextModelMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, nextModelMatrix);
	if (!checkCollision(nextModelMatrix[12], nextModelMatrix[14])) {
		// no collision, apply the movement
		glGetFloatv(GL_MODELVIEW_MATRIX, context.cow.local_coords);
	}

	// load the old matrix again
	glLoadMatrixf(viewModelMatrix);

	glutPostRedisplay();
}

void normalKeys(unsigned char key, int, int) {
	GLfloat cameraSpeed = 2.0;

	//  The 'y' coordinate is up and the cow is at the origin
	float cameraDistance = sqrt(
		pow(context.camera.camera_position[0], 2) +
		pow(context.camera.camera_position[2], 2)
	);

	// Initial angle of the camera (in radians)
	float cameraAngle = atan2(context.camera.camera_position[2], context.camera.camera_position[0]);

	switch (key) {
	case 'a':
		// Move the camera counterclockwise
		cameraAngle += 0.1;

		// Calculate the new position
		context.camera.camera_position[0] = cos(cameraAngle) * cameraDistance;
		context.camera.camera_position[2] = sin(cameraAngle) * cameraDistance;
		break;
	case 'd':
		// Move the camera clockwise
		cameraAngle -= 0.1;

		// Calculate the new camera position
		context.camera.camera_position[0] = cos(cameraAngle) * cameraDistance;
		context.camera.camera_position[2] = sin(cameraAngle) * cameraDistance;
		break;
	case 'w':
		// Move camera upward
		if(context.camera.camera_position[1] < 30) { // Set the maximum height
			context.camera.camera_position[1] += 0.1 * cameraSpeed;
		}
		break;
	case 's':
		// Check if the camera is above ground level before moving it downward
		if(context.camera.camera_position[1] > 0.5 * cameraSpeed) {
			context.camera.camera_position[1] -= 0.1 * cameraSpeed;
		}
		break;
	}

	// After updating camera's position and target
	context.camera.SetPosition(context.camera.camera_position[0], context.camera.camera_position[1], context.camera.camera_position[2]);
	context.camera.SetTarget(context.camera.camera_target[0], context.camera.camera_target[1], context.camera.camera_target[2]);

	// Update camera view
	context.camera.UpdateView();

	glutPostRedisplay();
}

/*
* drawScene: This function is responsible for drawing all the objects in the scene. It is called
* within the 'display' function.
*/
void drawScene() {
	
	glPushMatrix();
	// Translate to the point light position
	glTranslatef(context.pointlight.position[0], context.pointlight.position[1], context.pointlight.position[2]);
	context.pointlight.addLight();  // Add the point light at the current position
	glPopMatrix();

	glPushMatrix();
	// Translate to the spotlight position
	glTranslatef(context.spotlight.position[0], context.spotlight.position[1], context.spotlight.position[2]);
	context.spotlight.addlight(); 	// Add the spotlight at the current position

	glPopMatrix();

	glPushMatrix();
	glTranslatef(context.spotlight.position[0], context.spotlight.position[1], context.spotlight.position[2]);
	context.spotlight.draw(); // draw the spotlight (static) in the scene
	glPopMatrix();

	glPushMatrix();
	glTranslatef(context.pointlight.position[0], context.pointlight.position[1], context.pointlight.position[2]);
	context.pointlight.draw(); // Draw the 'moving' ambient light
	glPopMatrix();

	glPushMatrix();
	context.ground.draw(); // Draw the ground on the scene
	glPopMatrix();

	glPushMatrix();
	context.forest.draw(); // Draw the forest on the scene
	glPopMatrix();

	glPushMatrix();
	context.farmhouse.draw();  // Draw the farmhouse on the scene
	glPopMatrix();

	glPushMatrix();
	context.lake.draw();  // Draw the lake on the scene
	glPopMatrix();
	
	// Draw each stalk of wheat in the wheat field
	glPushMatrix();
	for (auto& wheat : context.wheatField) {
		wheat.draw();
	}
	glPopMatrix();

	glPushMatrix();
	glMultMatrixf(context.cow.local_coords); // Apply the cow's transformation matrix
	context.cow.draw();
	glPopMatrix();
	context.fence.draw({ 0, 1 }); // Draw the fence around the scene at the given location
}

/*
* display: This function handles the rendering of the whole scene. It updates the cow's transformation 
* matrix based on the user input and changes the view mode between the camera view and the cow's view.
* It also updates the lighting of the scene and calls the 'drawScene' function. After rendering all
* the objects, it handles the GUI display.
*/
void display() {
	static float time = 0.0f; // A static variable is declared to keep track of time. Being static, it preserves its value across function calls.

	// Position of pointlight oscillates along x-axis, with the oscillation determined by the sine of the time variable.
	context.pointlight.position[0] = 15.0f * sin(time); 

	time += 0.005f; // The time variable is incremented by a small amount after each call.

	// Start a new frame in the ImGui context, using the OpenGL2 and FreeGLUT bindings.
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplFreeGLUT_NewFrame();
	
	// Handle interactions for the menu.
	menu.handleInteraction();

	// Render ImGui's current frame.
	ImGui::Render();	
	
	// Obtain a reference to the ImGui context's IO structure.
	ImGuiIO& io = ImGui::GetIO();

	// Set the viewport to match the ImGui context's display size.
	glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);

	// Clear the color, depth, and stencil buffers to prepare for new rendering.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Load the projection matrix and reset it.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the perspective for the view.
	gluPerspective(40.0, io.DisplaySize.x / io.DisplaySize.y, 1.0, 150.0);

	// Load the modelview matrix and reset it.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// If the cow has a next move defined, execute it and update the cow's local transformation matrix.
	if (context.cow.next_move) {
		context.cow.is_moving = true;
		GLfloat viewModelMatrix[16];

		// Capture the current modelview matrix.
		glGetFloatv(GL_MODELVIEW_MATRIX, viewModelMatrix);

		// Load the cow's current local transformation matrix, execute the next move, and reset the move.
		glLoadMatrixf(context.cow.local_coords);
		context.cow.next_move();
		context.cow.next_move = nullptr;

		// Capture the updated transformation matrix and restore the original modelview matrix.
		glGetFloatv(GL_MODELVIEW_MATRIX, context.cow.local_coords);
		glLoadMatrixf(viewModelMatrix);
	}
	
	// Check if the first-person view from the cow is enabled.
	if (context.isCowView) {
		GLfloat viewModelMatrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, viewModelMatrix);
		glLoadMatrixf(context.cow.local_coords);

		// Apply the cow's current head rotation and position offsets to the view matrix.
		glRotatef(context.cow.head_vertical_angle, 1, 0, 0);
		glRotatef(context.cow.head_horizontal_angle, 0, 1, 0);
		glTranslated(0, 0.75, 0.9);

		// Capture the updated view matrix.
		GLfloat cameraPoseInDogView[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, cameraPoseInDogView);

		// Restore the original view matrix.
		glLoadMatrixf(viewModelMatrix);

		// Calculate the view angles based on the updated view matrix.
		GLfloat zAngle = atan2(-cameraPoseInDogView[2], cameraPoseInDogView[0]);
		GLfloat yAngle = atan2(-cameraPoseInDogView[9], cameraPoseInDogView[5]);
		
		// Apply the calculated view angles to the view matrix.
		gluLookAt(cameraPoseInDogView[12], cameraPoseInDogView[13], cameraPoseInDogView[14],
			sin(zAngle) + cameraPoseInDogView[12],-yAngle + cameraPoseInDogView[13],
			cos(zAngle) + cameraPoseInDogView[14],0, 1, 0);
	}
	else
	{
		// In case of third-person view, set the view matrix based on the camera's position and target.
		gluLookAt(context.camera.camera_position[0], context.camera.camera_position[1],
			context.camera.camera_position[2],context.camera.camera_target[0], context.camera.camera_target[1],
			context.camera.camera_target[2], 0, 1, 0);
	}

	// Set the global ambient light intensity.
	GLfloat globalAmbientVec[4] = { context.globalAmbient, context.globalAmbient, context.globalAmbient, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientVec);

	// Draw the scene
	drawScene();	
	

	// ImGui doesn't handle lighting well, so disable lighting, render ImGui's data, then re-enable lighting.
	glDisable(GL_LIGHTING);
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	glEnable(GL_LIGHTING);

	// Flush OpenGL's command buffer to make sure all commands get executed.
	glFlush();

	// Swap the front and back buffers, which displays the scene that we just rendered.
	glutSwapBuffers();

	// Post a redisplay event to trigger a new display callback.
	glutPostRedisplay();
}

/*
* This function is the entry point of the program. It sets up the GLUT display mode and window,
* initializes ImGui and its bindings, registers the keyboard input functions, sets up OpenGL parameters,
* initializes different scene objects, and starts the GLUT main loop.
*/
int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    
    // Set the option for GLUT's behaviour when the window is closed. In this case, it's set to return from the main loop.
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    // Initialize the display mode for the window to be created
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_STENCIL);

    // Set the initial window position.
    glutInitWindowPosition(80, 80);

    // Set the initial window size.
    glutInitWindowSize(1024, 600);

    // Create a window with a title.
    glutCreateWindow("Cow in the meadow - Maman17 - Project - 203439385");

    // Set the function to call when GLUT needs to display (or re-display) the window.
    glutDisplayFunc(display);

    // Initialize ImGui context.
    ImGui::CreateContext();

    // Set up ImGui to work with FreeGLUT.
    ImGui_ImplFreeGLUT_Init();
    ImGui_ImplFreeGLUT_InstallFuncs();

    // Set up ImGui to work with OpenGL2.
    ImGui_ImplOpenGL2_Init();

    // Set the GLUT functions to call in response to key events. The actual functions are not included in this snippet.
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(normalKeys);

    // Set up OpenGL. This includes enabling smooth shading, lighting, and depth testing, and setting blending options.
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize a wheat field in the global context by creating a grid of Wheat objects.
	Wheat::createField(context.wheatField);
	
    // Enable the point light and the spotlight in the global context.
    context.pointlight.enable();
    context.spotlight.enable();

    // Initialize the cow in the global context.
    context.cow.init();

    // Create a forest with 3 trees.
    context.forest = Forest(3); 

    // Set the GUI style to ImGui's dark style.
    ImGui::StyleColorsDark();

    // Start the GLUT main loop. This will run until it's told to return (see the GLUT_ACTION_ON_WINDOW_CLOSE option set earlier).
    glutMainLoop();

    // Cleanup ImGui and GLUT after the main loop has exited.
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplFreeGLUT_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
