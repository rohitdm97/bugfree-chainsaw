#version 330 core

out vec4 out_color;

in vec4 position;
in vec3 normal;
in vec3 color;
in vec2 texuv;

uniform sampler2D tex0;

struct Material {
	sampler2D diffuse;
	sampler2D specular;

	float shininess;
};
uniform Material material;

struct Light {
	vec4 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

uniform vec3 camera_position;

vec4 point_light() {
	vec3 norm = normalize(normal);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texuv));

	vec3 lightDir = normalize(light.position.xyz - position.xyz);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, texuv)));

	vec3 viewDir = normalize(camera_position - position.xyz);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specular, texuv)));

	return vec4(ambient + diffuse + specular, 1.0);
}

void main()
{
	out_color = point_light();
}
