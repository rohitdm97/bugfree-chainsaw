#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <debug.h>

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;

extern glm::vec3 origin;
extern glm::vec3 x_axis;
extern glm::vec3 y_axis;
extern glm::vec3 z_axis;

Camera::Camera()
{
}

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

void Camera::LookAt(glm::vec3 target)
{
	Camera::target = target;
	glm::vec3 front = glm::normalize(target - position);
	pitch = glm::degrees(asin(front.y));
	yaw = glm::degrees(asin(front.z / cos(glm::radians(pitch))));

	// update other vectors
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
	Camera::target = position + (front.operator*=(3 * sqrt(3)));

	// also re-calculate the Right and Up vector
	Camera::right = glm::normalize(glm::cross(front, y_axis));
	Camera::up = glm::normalize(glm::cross(right, front));

	glm::mat4 proj = glm::perspective(glm::radians(zoom), (float)width / height, near, far);
	Camera::matrix = proj * glm::lookAt(position, position + front, up);
}

void Camera::Export(Shader& shader)
{
	shader.SetMat4("camera", matrix);
	shader.SetVec3("camera_position", position);
}

void printTo(std::ostream& cout, glm::vec3 vec);
void printTo(std::ostream& cout, glm::mat4 mat);

void Camera::Print() {
	std::cout << "Camera[";
	std::cout << "pos = ("; printTo(std::cout, position); std::cout << ")";
	std::cout << ", width=" << width;
	std::cout << ", height=" << height;
	std::cout << ", yaw=" << yaw;
	std::cout << ", pitch=" << pitch;
	std::cout << ", speed=" << speed;
	std::cout << ", sensitivity=" << sensitivity;
	std::cout << ", zoom=" << zoom;
	std::cout << ", pitch=" << pitch;
	std::cout << "front = ("; printTo(std::cout, front); std::cout << ")";
	std::cout << "target = ("; printTo(std::cout, target); std::cout << ")";
	std::cout << "right = ("; printTo(std::cout, right); std::cout << ")";
	std::cout << "up = ("; printTo(std::cout, up); std::cout << ")";
	std::cout << "matrix = ("; printTo(std::cout, matrix); std::cout << ")";
	std::cout << "]" << std::endl;
}

