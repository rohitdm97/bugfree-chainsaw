#version 330 core

out vec4 out_color;

in vec3 position;
in vec2 texuv;

uniform sampler2D tex0;

vec4 orange = vec4(1, 0.5, 0, 1);
vec4 l_blue = vec4(0.18, 0.51, 0.62, 1);

vec4 white = vec4(1, 1, 1, 1);
vec4 black = vec4(0, 0, 0, 1);

float pi = 3.14159265;

void main()
{
	float lambda = 0.1;
	float x_2 = pow(position.x - 0.5, 2);
	float y_2 = pow(position.y - 0.5, 2);
	float gradient = sin((2 * pi/ lambda) * (x_2 + y_2));
	// out_color = mix(white, black, clamp(gradient, 0, 1));

	out_color = texture(tex0, texuv);
}
