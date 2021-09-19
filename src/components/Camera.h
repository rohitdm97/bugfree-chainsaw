#pragma once
#ifndef __CAMERA_CLASS_H
#define __CAMERA_CLASS_H

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include"render/Shader.h"

const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 target;
private:
	float near = 0.1f;
	float far = 100.0f;
	// primary
	int width, height;
	// position of camera with respect to world coord
	float yaw, pitch;

	// for change of position
	float speed;
	// for change in yaw/pitch
	float sensitivity;
	// for FOV value
	float zoom;

	// derived
	// unit vector showing where camera is looking towards.
	// so the target of camera is always position + front
	glm::vec3 front;
	// vector represents right direction is camera's view
	glm::vec3 right;
	// vector represents up direction is camera's view
	glm::vec3 up;

	glm::mat4 matrix;

	// using the info update the remaining vectors and matrix
	void updateVectors();
public:
	enum Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};
	Camera();
	Camera(glm::vec3 postion, int width, int height);
	Camera(glm::vec3 postion, int width, int height, float yaw, float pitch);

	void LookAt(glm::vec3 target);

	void Export(Shader& shader);

	void ProcessKeyboard(Movement move, double delta);
	void ProcessMouseMovement(float xoffset, float yoffset);
	void ProcessMouseScroll(float yoffset);

	void Print();
};

#endif // !__CAMERA_CLASS_H

