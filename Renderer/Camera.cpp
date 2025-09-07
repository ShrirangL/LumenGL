#include "Camera.h"

Camera::Camera()
	: mCameraPosition(glm::vec3(0.0f, 2.0, 10.0)), mCameraFront(glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - mCameraPosition)), mCameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	 mFieldOfView(45.0f), mHorizontalAngle(-90.0f), mVerticalAngle(0.0f), mSensitivity(0.005f),
	mScreenWidth(1600), mScreenHeight(1200), mNearDistance(0.1f), mFarDistance(300.0f),
	mLightPosition(glm::vec3(0.0f, 15.0f, 0.0f)), mLightColor(glm::vec3(1.0f, 1.0f, 1.0f))
{
	updateDirectionVector();

	updateViewMatrix();
	updateProjectionMatrix();
}

Camera& Camera::getInstance()
{
	static Camera instance;
	return instance;
}

void Camera::updateDirectionVector()
{
	glm::vec3 front;
	front.x = cos(glm::radians(mHorizontalAngle)) * cos(glm::radians(mVerticalAngle));
	front.y = sin(glm::radians(mVerticalAngle));
	front.z = sin(glm::radians(mHorizontalAngle)) * cos(glm::radians(mVerticalAngle));
	mCameraFront = glm::normalize(front);
}

void Camera::processKeyboardInput(GLFWwindow* window)
{
    glm::vec3 cameraRight = glm::normalize(glm::cross(mCameraFront, mCameraUp));

    // Movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        mCameraPosition += mSensitivity * mCameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        mCameraPosition -= mSensitivity * mCameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        mCameraPosition -= cameraRight * mSensitivity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        mCameraPosition += cameraRight * mSensitivity;

    // Rotation
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        mHorizontalAngle -= mSensitivity;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        mHorizontalAngle += mSensitivity;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        mVerticalAngle += mSensitivity;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        mVerticalAngle -= mSensitivity;

    // Clamp pitch
    if (mVerticalAngle > 89.0f)
        mVerticalAngle = 89.0f;
    if (mVerticalAngle < -89.0f)
        mVerticalAngle = -89.0f;

    updateDirectionVector();
    updateViewMatrix();
}

void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Camera::getInstance().processScroll(yoffset);
}

void Camera::processScroll(float yoffset)
{
	mFieldOfView -= (float)yoffset;
	mFieldOfView = glm::clamp(mFieldOfView, 0.1f, 100.0f);
	updateProjectionMatrix();
}

void Camera::updateViewMatrix()
{
	mViewMatrix = glm::lookAt(mCameraPosition, mCameraPosition + mCameraFront, mCameraUp);
}

void Camera::updateProjectionMatrix()
{
	mProjectionMatrix = glm::perspective(glm::radians(mFieldOfView), mScreenWidth / mScreenHeight, mNearDistance, mFarDistance);
}

const glm::mat4& Camera::getViewMatrix() const
{
	return mViewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
	return mProjectionMatrix;
}

const glm::vec3& Camera::getLightPosition() const
{
	return mLightPosition;
}

const glm::vec3& Camera::getLightColor() const
{
	return mLightColor;
}

const float Camera::getScreenWidth() const
{
    return mScreenWidth;
}

const float Camera::getScreenHeight() const
{
    return mScreenHeight;
}

glm::vec3 Camera::getPosition() const
{
	return mCameraPosition;
}
