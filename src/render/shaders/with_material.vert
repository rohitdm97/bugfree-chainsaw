#version 330 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec3 in_color;
layout (location = 3) in vec2 in_texuv;

out vec4 position;
out vec3 normal;
out vec3 color;
out vec2 texuv;

uniform mat4 model;
uniform mat4 camera;

void main()
{
	position = model * vec4(in_pos, 1.0f);
	normal = mat3(transpose(inverse(model))) * in_normal;
	color = in_color;
	texuv = in_texuv;

	gl_Position = camera * position;
}
