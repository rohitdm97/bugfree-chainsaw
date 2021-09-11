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
private:
	float near = 0.1f;
	float far = 100.0f;
	// primary
	int width, height;
	// position of camera with respect to world coord
	glm::vec3 position;
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
	Camera(glm::vec3 postion, int width, int height);
	Camera(glm::vec3 postion, int width, int height, float yaw, float pitch);

	void Export(Shader& shader);

	void ProcessKeyboard(Movement move, double delta);
	void ProcessMouseMovement(float xoffset, float yoffset);
	void ProcessMouseScroll(float yoffset);
private:
	void print(std::ostream& cout) {
		cout << "Camera[";
		cout << "pos = ("; print(cout, position); cout << ")";
		cout << ", width=" << width;
		cout << ", height=" << height;
		cout << ", yaw=" << yaw;
		cout << ", pitch=" << pitch;
		cout << ", speed=" << speed;
		cout << ", sensitivity=" << sensitivity;
		cout << ", zoom=" << zoom;
		cout << ", pitch=" << pitch;
		cout << "front = ("; print(cout, front); cout << ")";
		cout << "right = ("; print(cout, right); cout << ")";
		cout << "up = ("; print(cout, up); cout << ")";
		cout << "matrix = ("; print(cout, matrix); cout << ")";
		cout << "]" << std::endl;
	}
	void print(std::ostream& cout, glm::vec3 vec) {
		cout << vec.x << "," << vec.y << "," << vec.z;
	}
	void print(std::ostream& cout, glm::mat4 mat) {
		cout << std::endl;
		cout << mat[0].x << "," << mat[0].y << "," << mat[0].z << std::endl;
		cout << mat[1].x << "," << mat[1].y << "," << mat[1].z << std::endl;
		cout << mat[2].x << "," << mat[2].y << "," << mat[2].z << std::endl;
		cout << mat[3].x << "," << mat[3].y << "," << mat[3].z << std::endl;
	}
};

#endif // !__CAMERA_CLASS_H

