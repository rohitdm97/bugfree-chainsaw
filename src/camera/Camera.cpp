#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <debug.h>

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;

glm::vec3 origin = glm::vec3(0, 0, 0);
glm::vec3 x_axis = glm::vec3(1, 0, 0);
glm::vec3 y_axis = glm::vec3(0, 1, 0);
glm::vec3 z_axis = glm::vec3(0, 0, 1);

Camera::Camera(glm::vec3 position, int width, int height) :
	Camera(position, width, height, YAW, PITCH)
{}

Camera::Camera(
	glm::vec3 position,
	int width, int height,
	float yaw, float pitch
) : width(width), height(height), speed(SPEED), sensitivity(SENSITIVITY), zoom(ZOOM)
{
	Camera::position = position;
	Camera::yaw = yaw;
	Camera::pitch = pitch;
	Camera::updateVectors();
}

void Camera::ProcessKeyboard(Camera::Movement direction, double delta)
{
	float velocity = (float)(speed * delta);
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;

	Camera::updateVectors();
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	// update Front, Right and Up Vectors using the updated Euler angles
	Camera::updateVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	zoom -= (float) yoffset;
	if (zoom < 1.0f) zoom = 1.0f;
	if (zoom > 45.0f) zoom = 45.0f;

	Camera::updateVectors();
}

void Camera::updateVectors() {
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	Camera::front = glm::normalize(front);

	// also re-calculate the Right and Up vector
	Camera::right = glm::normalize(glm::cross(front, y_axis));
	Camera::up = glm::normalize(glm::cross(right, front));

	glm::mat4 proj = glm::perspective(glm::radians(zoom), (float)width / height, near, far);
	Camera::matrix = proj * glm::lookAt(position, position + front, up);
}

void Camera::Export(Shader& shader)
{
	shader.SetMat4("camera", matrix);
}

