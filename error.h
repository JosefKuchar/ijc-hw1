// error.h
// Řešení IJC-DU1, příklad a), 20.3.2111
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

void warning_msg(const char* fmt, ...);

void error_exit(const char* fmt, ...);

#endif  // ERROR_H_INCLUDED
