#pragma once

#ifndef __SHADER_CLASS_H
#define __SHADER_CLASS_H

#include<glad/glad.h>
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
};

#endif // !__SHADER_CLASS_H


