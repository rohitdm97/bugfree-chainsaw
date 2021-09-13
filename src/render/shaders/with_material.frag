#version 330 core

out vec4 out_color;

in vec4 position;
in vec3 normal;
in vec3 color;
in vec2 texuv;

uniform sampler2D tex0;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float shininess;
};
uniform Material material;

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

uniform vec3 camera_position;

vec4 point_light() {
	vec3 norm = normalize(normal);
	vec3 material_ambient = vec3(0.2);
	vec3 material_diffuse = vec3(0.5);
	vec3 material_specular = vec3(0.5);
	float material_shininess = 32;

	vec3 ambient = light.ambient * material_ambient;

	vec3 lightDir = normalize(light.position - position.xyz);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material_diffuse);

	vec3 viewDir = normalize(camera_position - position.xyz);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material_shininess);
	vec3 specular = light.specular * (spec * material_specular);

	return vec4(ambient + diffuse + specular, 1.0);
}

void main()
{
	out_color = point_light() * texture(tex0, texuv);
}
