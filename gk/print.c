#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h> /* Include this for snprintf */
#include <ctype.h>

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

char rot13(char c)
{
    if (isalpha(c))
    {
        char base = (isupper(c)) ? 'A' : 'a';
        return ((c - base + 13) % 26 + base);
    }
    return c;
}

void print_reversed_string(char *buffer, int *index, const char *str)
{
    int length = strlen(str);
    int i; /* Declare i outside the loop in C90 */
    for (i = length - 1; i >= 0; i--)
    {
        print_to_buffer(buffer, index, str[i]);
    }
}

/* Rest of the code */

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
            switch (*format)
            {
                /* Cases for other specifiers */

                case 'd':
                case 'i':
                    {
                        int num = va_arg(args, int);
                        char num_str[BUFFER_SIZE];
                        int i; /* Declare i outside the loop in C90 */
                        int num_length = snprintf(num_str, BUFFER_SIZE, "%d", num);
                        for (i = 0; i < num_length; i++)
                        {
                            print_to_buffer(buffer, &buffer_index, num_str[i]);
                        }
                    }
                    break;

                case 'u':
                    {
                        unsigned int num = va_arg(args, unsigned int);
                        char num_str[BUFFER_SIZE];
                        int i; /* Declare i outside the loop in C90 */
                        int num_length = snprintf(num_str, BUFFER_SIZE, "%u", num);
                        for (i = 0; i < num_length; i++)
                        {
                            print_to_buffer(buffer, &buffer_index, num_str[i]);
                        }
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

