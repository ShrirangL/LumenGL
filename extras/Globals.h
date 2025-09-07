#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include<memory>

class IDrawable;
class ObjectManager;
struct Point;

extern ObjectManager gObjectManager;

//Light Source
extern glm::vec3 gLightPos;
extern glm::vec3 gLightColor;

// Camera
extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;
extern float deltaTime;
extern float lastFrame;

extern float lastX;
extern float lastY; // Initial center of screen
extern bool firstMouse;

extern float fieldOfView;

extern float horizontalAngle; // Facing -Z initially
extern float verticalAngle;
extern float sensitivity; // Degrees per key press

extern glm::mat4 gView;
extern glm::mat4 gProjection;

extern std::string oldVertexShaderSource;
extern std::string oldFragmentShaderSource;
extern std::string edgeFragmentShaderSource;

extern std::string vertexShaderSource;
extern std::string planetFragmentShaderSource;
extern std::string sunFragmentShaderSource;

GLFWwindow* InitOpenGL();
void InitImGui(GLFWwindow* window);
void displayToolbar();

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void displayLineButton();
void displayTriangleButton();
void displayRectangleButton();
void displayCircleButton();
void displayCuboidButton();
void displayCylinderButton();
void displaySphereButton();