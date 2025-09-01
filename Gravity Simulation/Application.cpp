#include "IndexBuffer.h"
#include "Texture.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayoutElement.h"
#include "Program.h"
#include "Renderer.h"
#include "Cuboid.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Grid.h"
#include "Globals.h"
#include "Line.h"
#include "ObjectManager.h"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include "Camera.h"
#include "GUI.h"

int main()
{
	GLFWwindow* window = InitOpenGL();
	GUI gui(window);

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		Camera::getInstance().processKeyboardInput(window);
		Renderer::getInstance().clearScreen();
		ObjectManager::getInstance().drawShapes();
		gui.displayToolbar();
		endFrame(window);
	}

	gui.terminateGUI();
	terminateOpenGL(window);
	return 0;
}