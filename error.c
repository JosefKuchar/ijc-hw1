// error.c
// Řešení IJC-DU1, příklad a), 20.3.2111
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#include "error.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

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
