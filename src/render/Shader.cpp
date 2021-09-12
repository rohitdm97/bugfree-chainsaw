#include"Shader.h"
#include <debug.h>
#include <glm/gtc/type_ptr.hpp>

// Reads a text file and outputs a string with everything in the text file
string get_file_contents(string filename)
{
	std::ifstream in(filename, std::ios::binary);
	bool open = in.is_open();
	if (in)
	{
		// seek to end, check current index (get file size), resize the buffer
		// then dump everything in buffer
		std::string buffer;
		in.seekg(0, std::ios::end);
		buffer.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&buffer[0], buffer.size());
		in.close();
		return(buffer);
	}
	throw(errno);
}

Shader::Shader(const char* name)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents("src/render/shaders/" + string(name) + ".vert");
	std::string fragmentCode = get_file_contents("src/render/shaders/" + string(name) + ".frag");

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// OpenGL needs array of sources so we send &vertexSource
	// it reads one source as (&vertexSource)[0] == vertexSource

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();

	// Create Vertex Shader Object and get its reference
	// Attach Vertex Shader source to the Vertex Shader Object
	// Compile the Vertex Shader into machine code
	// Checks if Shader compiled succesfully

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");
	glAttachShader(ID, vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");
	glAttachShader(ID, fragmentShader);

	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);

	// Checks if Shaders linked succesfully
	compileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	INFO("Shaders are created");
}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::SetVec3(const char* name, glm::vec3 vec3)
{
	glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(vec3));
}

void Shader::SetMat4(const char* name, glm::mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

// Checks if the different Shaders have compiled properly
void Shader::compileErrors(GLuint shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}
