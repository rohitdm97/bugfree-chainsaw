#version 330 core

out vec4 out_color;

in vec3 position;
in vec2 texuv;

uniform sampler2D tex0;

void main()
{
	out_color = texture(tex0, texuv);
}
