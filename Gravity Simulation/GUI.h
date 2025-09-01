#pragma once
class GLFWwindow;

class GUI
{
	void displayLineButton();
	void displayTriangleButton();
	void displayRectangleButton();
	void displayCircleButton();
	void displayCuboidButton();
	void displayCylinderButton();
	void displaySphereButton();
public:
	GUI(GLFWwindow* window);
	void displayToolbar();
	void terminateGUI();
};