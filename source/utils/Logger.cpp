#include "Logger.h"

#include <stdio.h>
#include <stdarg.h>

static FILE* output = nullptr;

void Logger::setOutput(FILE* output_) {
  output = output_;
}

void Logger::log(int level, const char* file, const char* func, int line,
		const char* fmt, ...) {
  fprintf(output, "[%s:%s:%d] ", file, func, line);

  switch(level) {
  case 0:
    fprintf(output, "DEBUG: ");
    break;
  case 1:
    fprintf(output, "INFO: ");
    break;
  case 2:
    fprintf(output, "WARNING: ");
    break;
  case 3:
    fprintf(output, "ERROR: ");
    break;
  case 4:
    fprintf(output, "FATAL: ");
    break;
  }

  va_list args;
  va_start(args, fmt);
  vfprintf(output, fmt, args);
  va_end(args);

  fprintf(output, "\n");

  if (level == 4) {
    exit(-1);
  }
}
