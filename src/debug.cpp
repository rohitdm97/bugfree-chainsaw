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
