#pragma once

#include <cstdio>

#define debug(fmt, ...) log(0, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define info(fmt, ...) log(1, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define warn(fmt, ...) log(2, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define yell(fmt, ...) log(3, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define aaah(fmt, ...) log(4, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

namespace Logger {
	void setOutput(FILE* output);

	// Levels:
	// 0 - Just for us. Not the user. ;)
	// 1 - Just say what's going on
	// 2 - Expected, but not ideal.
	// 3 - Unexpected but the program can keep going.
	// 4 - The program can't continue.
	void log(int level, const char* file, const char* func, int line,
			const char* fmt, ...);
}
