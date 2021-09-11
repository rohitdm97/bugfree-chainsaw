#version 330 core

layout (location = 1) in vec3 in_pos;

out vec3 position;

void main()
{
	position = /* model * */ in_pos;

	gl_Position = vec4(position, 1.0f);
}
