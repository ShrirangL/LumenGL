#include "Globals.h"
#include <iostream>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "IDrawable.h"
#include "Point.h"
#include "ObjectManager.h"

ObjectManager gObjectManager;

//Light Source
glm::vec3 gLightPos = glm::vec3(0.0f, 15.0f, 0.0f);
glm::vec3 gLightColor = glm::vec3(1.0f, 1.0f, 1.0f); // white light

float fieldOfView = 45.0f;
float horizontalAngle = -90.0f; // Facing -Z initially
float verticalAngle = 0.0f;
float sensitivity = 0.05f; // Degrees per key press

// Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 2.0, 10.0);
glm::vec3 cameraFront = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - cameraPos);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 gView = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

float screenWidth = 1600;
float screenHeight = 1200;
float nearDistance = 0.1f;
float farDistance = 300.0f;
glm::mat4 gProjection = glm::perspective(glm::radians(fieldOfView), screenWidth / screenHeight, nearDistance, farDistance);

std::string oldVertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main() {\n"
"    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
"}\n";

std::string oldFragmentShaderSource = R"glsl(
#version 330 core
out vec3 FragColor;

void main() {
	FragColor = vec3(1.0, 0.9, 0.3); // Sun color
}
)glsl";


std::string edgeFragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"	FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Black edges\n"
"}\n";

std::string vertexShaderSource = R"glsl(
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 vTexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	FragPos = aPos;        // Already in world space
	Normal = aNormal;      // Already in world space
	vTexCoord = aTexCoord;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)glsl";

std::string planetFragmentShaderSource = R"glsl(
#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 vTexCoord;

out vec4 FragColor;

uniform sampler2D u_Texture;
uniform bool u_UseTexture;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

	if (u_UseTexture)
	{
        vec3 textureColor = texture(u_Texture, vTexCoord).rgb;
		vec3 result = (ambient + diffuse + specular) * textureColor;
		FragColor = vec4(result, 1.0);
	}
    else
	{
        vec3 result = (ambient + diffuse + specular) * objectColor;
		FragColor = vec4(result, 1.0);
	}
}
)glsl";

std::string sunFragmentShaderSource = R"glsl(
#version 330 core

in vec2 vTexCoord;

out vec4 FragColor;

uniform sampler2D u_Texture;
uniform bool u_UseTexture;
uniform vec3 objectColor;

void main()
{
    vec3 color;
    if (u_UseTexture)
    {
        color = texture(u_Texture, vTexCoord).rgb;
    }
    else
    {
        color = objectColor;
    }

    FragColor = vec4(color, 1.0);
}
)glsl";


void processInput(GLFWwindow* window)
{
	float cameraSpeed = 0.005;

	// Movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	// Rotation
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		horizontalAngle -= sensitivity;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		horizontalAngle += sensitivity;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		verticalAngle += sensitivity;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		verticalAngle -= sensitivity;

	// Clamp pitch
	if (verticalAngle > 89.0f)
		verticalAngle = 89.0f;
	if (verticalAngle < -89.0f)
		verticalAngle = -89.0f;

	// Update cameraFront based on yaw and pitch
	glm::vec3 front;
	front.x = cos(glm::radians(horizontalAngle)) * cos(glm::radians(verticalAngle));
	front.y = sin(glm::radians(verticalAngle));
	front.z = sin(glm::radians(horizontalAngle)) * cos(glm::radians(verticalAngle));
	cameraFront = glm::normalize(front);

	gView = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fieldOfView -= (float)yoffset;

	// Clamp fov
	fieldOfView = fieldOfView < 0.1 ? 0.1 : fieldOfView;
	fieldOfView = fieldOfView > 100 ? 100 : fieldOfView;

	gProjection = glm::perspective(glm::radians(fieldOfView), screenWidth / screenHeight, nearDistance, farDistance);
}

GLFWwindow* InitOpenGL()
{
	//Initialize GLFW
	if (!glfwInit())
	{
		std::cerr << "Failed to intitalize GLFW" << std::endl;
		exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Model", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Failed to create window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	//initialize glew
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glEnable(GL_DEPTH_TEST);

	glfwSetScrollCallback(window, scroll_callback);

	return window;
}

void InitImGui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark(); // or Classic/Light

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330"); // Use the same GLSL version as your shaders

}

void displayToolbar()
{
	glDisable(GL_DEPTH_TEST);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2((float)screenWidth, 100)); // Adjust height as needed
	ImGui::Begin("Shape Toolbar", nullptr, ImGuiWindowFlags_NoTitleBar);

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20)); // Make buttons big

	// Example: Use text as icon, replace with images if available
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

void displayLineButton()
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
			gObjectManager.createLine(Point(point1_x, point1_y, point1_z), Point(point2_x, point2_y, point2_z));
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}

void displayTriangleButton()
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
			gObjectManager.createTriangle(Point(point1_x, point1_y, point1_z), Point(point2_x, point2_y, point2_z),
				Point(point3_x, point3_y, point3_z));
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}

void displayRectangleButton()
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
			gObjectManager.createRectangle(Point(bottomleft_x, bottomleft_y, bottomleft_z), Point(topright_x, topright_y, topright_z));
			ImGui::CloseCurrentPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}
void displayCircleButton()
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
			gObjectManager.createCircle(Point(circle_x, circle_y, circle_z), circle_radius);
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}
void displayCuboidButton()
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
			gObjectManager.createCuboid(Point(centre_x, centre_y, centre_z), cuboid_width, cuboid_height, cuboid_depth);
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}

void displayCylinderButton()
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
			gObjectManager.createCylinder(Point(bCentre_x, bCentre_y, bCentre_z), Point(tCentre_x, tCentre_y, tCentre_z), cylinder_radius);
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}
void displaySphereButton()
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
			gObjectManager.createSphere(Point(sphere_x, sphere_y, sphere_z), sphere_radius);
			ImGui::CloseCurrentPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}

