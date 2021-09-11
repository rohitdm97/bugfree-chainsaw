#version 330 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec3 in_color;
layout (location = 3) in vec2 in_texuv;

out vec3 position;
out vec2 texuv;

void main()
{
	position = /* model * */ in_pos;
	texuv = in_texuv;

	gl_Position = vec4(position, 1.0f);
}
