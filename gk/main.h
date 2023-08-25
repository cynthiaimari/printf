#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h> /* Include this for snprintf */
#include <ctype.h>

#define BUFFER_SIZE 1024

int _printf(const char *format, ...);

void flush_buffer(char *buffer, int *index);
void print_to_buffer(char *buffer, int *index, char c);
char rot13(char c);
void print_reversed_string(char *buffer, int *index, const char *str);

/* Declaration for the custom helper functions */
void print_string(char *buffer, int *index, const char *str);

#endif /* MAIN_H */

