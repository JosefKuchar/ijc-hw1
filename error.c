#include "error.h"
#include <stdarg.h>
#include <stdio.h>

void warning_msg(const char* fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, arg);
    va_end(arg);
}

void error_exit(const char* fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, arg);
    va_end(arg);
    exit(1);
}
