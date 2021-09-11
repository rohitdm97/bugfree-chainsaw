#version 330 core

out vec4 out_color;

in vec3 position;

vec4 orange = vec4(1, 0.5, 0, 1);
vec4 l_blue = vec4(0.18, 0.51, 0.62, 1);

void main()
{
	out_color = orange;
}
