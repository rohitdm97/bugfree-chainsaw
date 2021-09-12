#include "debug.h"

void __print_debug_info(const char* file, int line, const char* message)
{
	if (!debug)
	{
		return;
	}
	std::cout << "INFO: at [" << file << "](: " << line << ") " << std::endl << message << std::endl;
}

void __print_debug_warn(const char* file, int line, const char* message)
{
	if (!debug)
	{
		return;
	}
	std::cout << "WARN: at [" << file << "](: " << line << ") " << std::endl << message << std::endl;
}

void __print_debug_error(const char* file, int line, const char* message)
{
	if (!debug)
	{
		return;
	}
	std::cout << "ERROR: at [" << file << "](: " << line << ") " << std::endl << message << std::endl;
}

void printTo(std::ostream& cout, glm::vec3 vec) {
	cout << vec.x << "," << vec.y << "," << vec.z;
}
void printTo(std::ostream& cout, glm::mat4 mat) {
	cout << std::endl;
	cout << mat[0].x << "," << mat[0].y << "," << mat[0].z << std::endl;
	cout << mat[1].x << "," << mat[1].y << "," << mat[1].z << std::endl;
	cout << mat[2].x << "," << mat[2].y << "," << mat[2].z << std::endl;
	cout << mat[3].x << "," << mat[3].y << "," << mat[3].z << std::endl;
}

