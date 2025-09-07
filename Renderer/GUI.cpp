#include <GL/glew.h>  
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "GUI.h"
#include "Camera.h"
#include "ObjectManager.h"

GUI::GUI(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void GUI::displayToolbar()
{
	glDisable(GL_DEPTH_TEST);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2((float)Camera::getInstance().getScreenWidth(), 100));
	ImGui::Begin("Shape Toolbar", nullptr, ImGuiWindowFlags_NoTitleBar);

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));

	if (ImGui::Button("Line")) { ImGui::OpenPopup("Create Line"); } ImGui::SameLine();
	if (ImGui::Button("Triangle")) { ImGui::OpenPopup("Create Triangle"); } ImGui::SameLine();
	if (ImGui::Button("Rectangle")) { ImGui::OpenPopup("Create Rectangle"); } ImGui::SameLine();
	if (ImGui::Button("Circle")) { ImGui::OpenPopup("Create Circle"); } ImGui::SameLine();
	if (ImGui::Button("Cuboid")) { ImGui::OpenPopup("Create Cuboid"); } ImGui::SameLine();
	if (ImGui::Button("Cylinder")) { ImGui::OpenPopup("Create Cylinder"); } ImGui::SameLine();
	if (ImGui::Button("Sphere")) { ImGui::OpenPopup("Create Sphere"); }

	displayLineButton();
	displayTriangleButton();
	displayRectangleButton();
	displayCircleButton();
	displayCuboidButton();
	displayCylinderButton();
	displaySphereButton();

	ImGui::PopStyleVar();
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glEnable(GL_DEPTH_TEST);
}

void GUI::terminateGUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GUI::displayLineButton()
{
	static float point1_x = 0, point1_y = 0, point1_z = 0, point2_x = 1, point2_y = 1, point2_z = 0;
	if (ImGui::BeginPopupModal("Create Line", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::InputFloat("Point1 X", &point1_x);
		ImGui::InputFloat("Point1 Y", &point1_y);
		ImGui::InputFloat("Point1 Z", &point1_z);

		ImGui::InputFloat("Point2 X", &point2_x);
		ImGui::InputFloat("Point2 Y", &point2_y);
		ImGui::InputFloat("Point2 Z", &point2_z);

		if (ImGui::Button("Create"))
		{
			ObjectManager::getInstance().createLine(Point(point1_x, point1_y, point1_z), Point(point2_x, point2_y, point2_z));
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}

void GUI::displayTriangleButton()
{
	static float point1_x = 0, point1_y = 0, point1_z = 0, point2_x = 1, point2_y = 1, point2_z = 0,
		point3_x = 0, point3_y = 1, point3_z = 0;
	if (ImGui::BeginPopupModal("Create Triangle", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::InputFloat("Point1 X", &point1_x);
		ImGui::InputFloat("Point1 Y", &point1_y);
		ImGui::InputFloat("Point1 Z", &point1_z);
		ImGui::InputFloat("Point2 X", &point2_x);
		ImGui::InputFloat("Point2 Y", &point2_y);
		ImGui::InputFloat("Point2 Z", &point2_z);
		ImGui::InputFloat("Point3 X", &point3_x);
		ImGui::InputFloat("Point3 Y", &point3_y);
		ImGui::InputFloat("Point3 Z", &point3_z);
		if (ImGui::Button("Create"))
		{
			ObjectManager::getInstance().createTriangle(Point(point1_x, point1_y, point1_z), Point(point2_x, point2_y, point2_z),
				Point(point3_x, point3_y, point3_z));
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}

void GUI::displayRectangleButton()
{
	static float bottomleft_x = -1.0f, bottomleft_y = -1.0f, bottomleft_z = 0.0f,
		topright_x = 1.0f, topright_y = 1.0f, topright_z = 0.0f;
	if (ImGui::BeginPopupModal("Create Rectangle", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::InputFloat("Bottom Left X", &bottomleft_x);
		ImGui::InputFloat("Bottom Left Y", &bottomleft_y);
		ImGui::InputFloat("Bottom Left Z", &bottomleft_z);

		ImGui::InputFloat("Top Right X", &topright_x);
		ImGui::InputFloat("Top Right Y", &topright_z);
		ImGui::InputFloat("Top Right Z", &topright_z);

		if (ImGui::Button("Create"))
		{
			ObjectManager::getInstance().createRectangle(Point(bottomleft_x, bottomleft_y, bottomleft_z), Point(topright_x, topright_y, topright_z));
			ImGui::CloseCurrentPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}

void GUI::displayCircleButton()
{
	static float circle_radius = 1.0f, circle_x = 0, circle_y = 0, circle_z = 0;
	if (ImGui::BeginPopupModal("Create Circle", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::InputFloat("Center X", &circle_x);
		ImGui::InputFloat("Center Y", &circle_y);
		ImGui::InputFloat("Center Z", &circle_z);

		ImGui::InputFloat("Radius", &circle_radius);

		if (ImGui::Button("Create"))
		{
			ObjectManager::getInstance().createCircle(Point(circle_x, circle_y, circle_z), circle_radius);
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}

void GUI::displayCuboidButton()
{
	static float centre_x = 0, centre_y = 0, centre_z = 0, cuboid_width = 1, cuboid_height = 1, cuboid_depth = 1;
	if (ImGui::BeginPopupModal("Create Cuboid", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::InputFloat("Center X", &centre_x);
		ImGui::InputFloat("Center Y", &centre_y);
		ImGui::InputFloat("Center Z", &centre_z);

		ImGui::InputFloat("Width", &cuboid_width);
		ImGui::InputFloat("Height", &cuboid_height);
		ImGui::InputFloat("Depth", &cuboid_depth);
		if (ImGui::Button("Create"))
		{
			ObjectManager::getInstance().createCuboid(Point(centre_x, centre_y, centre_z), cuboid_width, cuboid_height, cuboid_depth);
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}

void GUI::displayCylinderButton()
{
	static float bCentre_x = 0, bCentre_y = 0, bCentre_z = 0, tCentre_x = 0, tCentre_y = 1, tCentre_z = 0, cylinder_radius = 1;
	if (ImGui::BeginPopupModal("Create Cylinder", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::InputFloat("Botttom Center X", &bCentre_x);
		ImGui::InputFloat("Botttom Center Y", &bCentre_y);
		ImGui::InputFloat("Botttom Center z", &bCentre_z);

		ImGui::InputFloat("Top Center X", &tCentre_x);
		ImGui::InputFloat("Top Center Y", &tCentre_y);
		ImGui::InputFloat("Top Center Z", &tCentre_z);

		ImGui::InputFloat("Radius", &cylinder_radius);

		if (ImGui::Button("Create"))
		{
			ObjectManager::getInstance().createCylinder(Point(bCentre_x, bCentre_y, bCentre_z), Point(tCentre_x, tCentre_y, tCentre_z), cylinder_radius);
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}

void GUI::displaySphereButton()
{
	static float sphere_x = 0, sphere_y = 0, sphere_z = 0, sphere_radius = 1;
	if (ImGui::BeginPopupModal("Create Sphere", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::InputFloat("Center X", &sphere_x);
		ImGui::InputFloat("Center Y", &sphere_y);
		ImGui::InputFloat("Center Z", &sphere_z);

		ImGui::InputFloat("Radius", &sphere_radius);

		if (ImGui::Button("Create"))
		{
			ObjectManager::getInstance().createSphere(Point(sphere_x, sphere_y, sphere_z), sphere_radius);
			ImGui::CloseCurrentPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}
