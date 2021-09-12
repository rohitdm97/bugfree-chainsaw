#pragma once

#ifndef __DEBUG_ADDED
#define __DEBUG_ADDED

#include <iostream>
#include <string>
#include <glm/glm.hpp>

static bool debug = true;

void __print_debug_info(const char* file, int line, const char* message);
void __print_debug_warn(const char* file, int line, const char* message);
void __print_debug_error(const char* file, int line, const char* message);

#define INFO(MESSAGE) __print_debug_info(__FILE__, __LINE__, MESSAGE)
#define WARN(MESSAGE) __print_debug_warn(__FILE__, __LINE__, MESSAGE)
#define ERROR(MESSAGE) __print_debug_error(__FILE__, __LINE__, MESSAGE)

void printTo(std::ostream& cout, glm::vec3 vec);
void printTo(std::ostream& cout, glm::mat4 mat);

#endif //!__DEBUG_ADDED
