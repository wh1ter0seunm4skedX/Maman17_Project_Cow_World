/*
* The Menu class encapsulates the GUI (Graphical User Interface) 
* functionality of the application using the ImGui library. It 
* interacts with an instance of the Context class to control 
* and manipulate various aspects of the rendered scene.
*/

#include "Menu.h"
#include "Context.h"
#include "imgui.h"

/*
* The constructor initializes a reference to a Context instance, 
* thereby allowing interaction with the current rendering context.
*/
Menu::Menu(Context& context) : context(context) {}

/*
* Method - handleInteraction():
* This method manages all ImGui-based interactions within the GUI. 
* ImGui::Begin() and ImGui::End() encapsulate the ImGui elements 
* and operations. The GUI consists of multiple panels and controls 
* grouped by functionality.
*/
void Menu::handleInteraction() {
    constexpr ImGuiWindowFlags window_flags = 0;
	if (ImGui::Begin("Properties", false, window_flags))
	{
		ImGui::RadioButton("Above mode", &context.isCowView, 0);
		ImGui::RadioButton("Eye mode", &context.isCowView, 1);

		if (ImGui::CollapsingHeader("Cow properties"))
		{
			ImGui::SliderFloat("head horizontal", &context.cow.head_horizontal_angle, -30.0f, 30.0f);
			ImGui::SliderFloat("head vertical", &context.cow.head_vertical_angle, -5.0f, 50.0f);
			ImGui::SliderFloat("tail horizontal", &context.cow.tail_horizontal_angle, -25.0f, 25.0f);
			ImGui::SliderFloat("tail vertical", &context.cow.tail_vertical_angle, -14.0f, 50.0f);
		}
	
		static bool pointlight = true;
		static bool spotlight = true;
		if (ImGui::CollapsingHeader("Lights"))
		{
			ImGui::SliderFloat("ambient light adjust", &context.globalAmbient, 0.0f, 1.0f);
			ImGui::Checkbox("Enable pointlight", &pointlight);
			
			ImGui::ColorEdit3("pointlight color", reinterpret_cast<float*>(&context.pointlight.color));
			ImGui::SliderFloat("pointlight source x", &context.pointlight.position[0], -10.0f, 10.0f);
			ImGui::SliderFloat("pointlight source y", &context.pointlight.position[1], -10.0f, 10.0f);
			ImGui::SliderFloat("pointlight source z", &context.pointlight.position[2], -10.0f, 10.0f);

			ImGui::Checkbox("Enable spotlight", &spotlight);
			ImGui::ColorEdit3("spotlight color", reinterpret_cast<float*>(&context.spotlight.color));
			ImGui::SliderFloat("spotlight source x", &context.spotlight.position[0], -10.0f, 10.0f);
			ImGui::SliderFloat("spotlight source y", &context.spotlight.position[1], -10.0f, 10.0f);
			ImGui::SliderFloat("spotlight source z", &context.spotlight.position[2], -10.0f, 10.0f);
			ImGui::SliderFloat("spotlight target x", &context.spotlight.target[0], -10.0f, 10.0f);
			ImGui::SliderFloat("spotlight target y", &context.spotlight.target[1], -10.0f, 10.0f);
			ImGui::SliderFloat("spotlight target z", &context.spotlight.target[2], -10.0f, 10.0f);
			ImGui::SliderFloat("spotlight cutoff", &context.spotlight.cutoff, 0.0f, 90.0f);
			ImGui::SliderFloat("spotlight exponent", &context.spotlight.exponent, 0.0f, 90.0f);

			pointlight ? context.pointlight.enable() : context.pointlight.disable();
			spotlight ? context.spotlight.enable() : context.spotlight.disable();
		}
		
		if (ImGui::CollapsingHeader("Help (Change views, Movement & adjust lights)"))
		{
			ImGui::Text("Viewing modes:");
			ImGui::TextWrapped(("Two viewing modes exist: 'Above mode' and 'Eye mode. The 'Camera' section governs the external 'Above view', whereas the cow's head position and rotation explicitly control the 'Eye mode'."));
			ImGui::Spacing();

			ImGui::Text("Keyboard control:");
			ImGui::TextWrapped("You can use the arrow keys to control the cow's movements and 'w', 's', 'a', 'd' to control the camera. The detailed functions are as follows:");

			ImGui::BulletText("UP Arrow: Move the cow forward.");
			ImGui::BulletText("DOWN Arrow: Move the cow backward.");
			ImGui::BulletText("LEFT Arrow: Rotate the cow to the left.");
			ImGui::BulletText("RIGHT Arrow: Rotate the cow to the right.");

			ImGui::BulletText("'W': Move the camera upward.");
			ImGui::BulletText("'S': Move the camera downward.");
			ImGui::BulletText("'A': Rotate the camera counterclockwise.");
			ImGui::BulletText("'D': Rotate the camera clockwise.");

			ImGui::TextWrapped("Note: The cow cannot move if there is a collision. The camera's maximum height is 30 units, and it cannot move below the ground level.");
			ImGui::Spacing();

			ImGui::Text("Cow properties section:");
			ImGui::TextWrapped(("The cow section controls govern the head's vertical and horizontal orientation as well as the tail's vertical and horizontal orientation."));
			ImGui::Spacing();

			ImGui::Text("Lights section:");
			ImGui::TextWrapped(("The Light section controls dictate the lighting conditions of the scene. The 'pointlight' and 'spotlight' are two sources of light that can be toggled on or off. The global ambient light value can be adjusted using the 'ambient light adjust'. The spotlight's spatial position and target, as well as the pointlight's position, are also adjustable."));
			ImGui::Spacing();

		}

		if (ImGui::Button("Exit"))
		{
			exit(0);
		}
	}
	ImGui::End();
}
