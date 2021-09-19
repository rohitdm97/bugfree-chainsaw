#pragma once

#ifndef __SHADER_CLASS_H
#define __SHADER_CLASS_H

#include<glad/glad.h>
#include<glm/glm.hpp>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

typedef std::string string;

string get_file_contents(string);

/*
	The class that wraps Shader loading and linking to the program logic
	ID: Program ID
*/
class Shader
{
private:
	void compileErrors(GLuint shader, const char* type);
public:
	GLuint ID;
	Shader(const char* name);

	void Activate();
	void Delete();

	// setters for uniform
	void SetInt(const char* name, int value);
	void SetFloat(const char* name, float value);
	void SetVec3(const char* name, glm::vec3 vec3);
	void SetVec4(const char* name, glm::vec4 vec4);
	void SetMat4(const char* name, glm::mat4 matrix);
};

#endif // !__SHADER_CLASS_H


