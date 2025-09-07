#include "Globals.h"
#include <iostream>
#include "IDrawable.h"
#include "Point.h"
#include "ObjectManager.h"
#include "Camera.h"

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera::getInstance().processScroll(yoffset);
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

	GLFWwindow* window = glfwCreateWindow(Camera::getInstance().getScreenWidth(), Camera::getInstance().getScreenHeight(), "Model", nullptr, nullptr);
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

	glfwSetScrollCallback(window, Camera::scroll_callback);

	return window;
}

void endFrame(GLFWwindow* window)
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void terminateOpenGL(GLFWwindow* window)
{
	glfwDestroyWindow(window);
	glfwTerminate();
}


