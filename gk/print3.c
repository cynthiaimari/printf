#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>  /* Include va_list */
#include "main.h"

#define BUFFER_SIZE 1024

void flush_buffer(char *buffer, int *index)
{
    write(1, buffer, *index);
    *index = 0;
}

void print_to_buffer(char *buffer, int *index, char c)
{
    if (*index >= BUFFER_SIZE)
        flush_buffer(buffer, index);
    buffer[*index] = c;
    (*index)++;
}

void print_string(char *buffer, int *index, const char *str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        print_to_buffer(buffer, index, str[i]);
    }
}

/* Implement other helper functions as provided previously */

int _printf(const char *format, ...)
{
    va_list args;  /*Declare va_list*/
    char buffer[BUFFER_SIZE];
    int char_count = 0;
    int buffer_index = 0;

    va_start(args, format);
    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
                /* Cases for other specifiers */
                case 'd':
                case 'i':
                    {
                        int num = va_arg(args, int);
                        char num_str[BUFFER_SIZE];
                        snprintf(num_str, BUFFER_SIZE, "%d", num);
                        print_string(buffer, &buffer_index, num_str);
                    }
                    break;

                case 'u':
                    {
                        unsigned int num = va_arg(args, unsigned int);
                        char num_str[BUFFER_SIZE];
                        snprintf(num_str, BUFFER_SIZE, "%u", num);
                        print_string(buffer, &buffer_index, num_str);
                    }
                    break;

                /* Cases for other specifiers */

            }
        }
        else
        {
            print_to_buffer(buffer, &buffer_index, *format);
            char_count++;
        }
        format++;
        if (buffer_index >= BUFFER_SIZE)
            flush_buffer(buffer, &buffer_index);
    }
    flush_buffer(buffer, &buffer_index);
    va_end(args);
    return char_count;
}
