#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

/* Function to flush the buffer */
void flush_buffer(char *buffer, int *index)
{
    write(1, buffer, *index);
    *index = 0;
}

/* Function to print a character to the buffer */
void print_to_buffer(char *buffer, int *index, char c)
{
    if (*index >= BUFFER_SIZE)
        flush_buffer(buffer, index);
    buffer[*index] = c;
    (*index)++;
}

/* Function to print a string to the buffer */
void print_string(char *buffer, int *index, const char *str)
{
    while (*str != '\0')
    {
        print_to_buffer(buffer, index, *str);
        str++;
    }
}

int _printf(const char *format, ...)
{
    va_list args;
    char buffer[BUFFER_SIZE];
    int char_count = 0;
    int buffer_index = 0;

    va_start(args, format);
    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;
            /* Handle different conversion specifiers and custom cases */
            if (*format == 'c')
            {
                /* Handle character specifier */
                char c = va_arg(args, int);
                print_to_buffer(buffer, &buffer_index, c);
            }
            else if (*format == 's')
            {
                /* Handle string specifier */
                const char *str = va_arg(args, const char *);
                print_string(buffer, &buffer_index, str);
            }
            /* Handle other specifiers similarly */
            /* ... */
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
    /* Flush the remaining content in the buffer */
    flush_buffer(buffer, &buffer_index);
    va_end(args);
    return char_count;
}

