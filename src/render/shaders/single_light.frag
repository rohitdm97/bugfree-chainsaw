#version 330 core

out vec4 out_color;

in vec4 position;
in vec3 normal;
in vec3 color;
in vec2 texuv;

uniform sampler2D tex0;

uniform vec3 light_position;
uniform vec3 light_color;

uniform vec3 camera_position;

vec4 point_light() {
	vec3 norm = normalize(normal);

	vec3 ambient = light_color * color * 0.2;

	vec3 lightDir = normalize(light_position - position.xyz);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light_color * (diff * color);

	float specularStrength = 0.5;
	vec3 viewDir = normalize(camera_position - position.xyz);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = light_color * (spec * color);

	return vec4(ambient + diffuse + specular, 1.0);
}

void main()
{
	out_color = point_light() * texture(tex0, texuv);
}
