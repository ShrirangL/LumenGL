#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera 
{
    glm::vec3 mCameraPosition;
    glm::vec3 mCameraFront;
    glm::vec3 mCameraUp;

    float mFieldOfView;
    float mHorizontalAngle;
    float mVerticalAngle;
    float mSensitivity;

    float mScreenWidth;
    float mScreenHeight;
    float mNearDistance;
    float mFarDistance;

    glm::mat4 mViewMatrix;
    glm::mat4 mProjectionMatrix;
              
    glm::vec3 mLightPosition;
    glm::vec3 mLightColor;

    Camera();
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;
public:
    static Camera& getInstance();
    void processKeyboardInput(GLFWwindow* window);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    void updateDirectionVector();
    void processScroll(float yoffset);
    void updateViewMatrix();
    void updateProjectionMatrix();

    const glm::mat4& getViewMatrix() const;
    const glm::mat4& getProjectionMatrix() const;

	const glm::vec3& getLightPosition() const;
	const glm::vec3& getLightColor() const;

    const float getScreenWidth() const;
    const float getScreenHeight() const;

    glm::vec3 getPosition() const;
};
