#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

void flush_buffer(char *buffer, int *index) {
    write(1, buffer, *index);
    *index = 0;
}

void print_to_buffer(char *buffer, int *index, char c) {
    if (*index >= BUFFER_SIZE)
        flush_buffer(buffer, index);
    buffer[*index] = c;
    (*index)++;
}

char rot13(char c) {
    if (isalpha(c)) {
        char base = (isupper(c)) ? 'A' : 'a';
        return (c - base + 13) % 26 + base;
    }
    return c;
}

int _printf(const char *format, ...) {
    va_list args;
    char buffer[BUFFER_SIZE];
    int char_count = 0;
    int buffer_index = 0;

    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            /* ... (flag handling and other code as before)*/

            /* Handle different conversion specifiers and custom cases*/
            if (*format == 'c') {
                /* ... (same 'c' case implementation as before)*/
            }
            else if (*format == 's') {
                /* ... (same 's' case implementation as before)*/
            }
            else if (*format == 'd' || *format == 'i') {
                /* ... (same integer handling code as before)*/
            }
            else if (*format == 'u') {
                /* ... (same 'u' case implementation as before)*/
            }
            else if (*format == 'o') {
                /* ... (same 'o' case implementation as before)*/
            }
            else if (*format == 'x') {
                /* ... (same 'x' case implementation as before)*/
            }
            else if (*format == 'X') {
                /* ... (same 'X' case implementation as before)*/
            }
            else if (*format == 'p') {
                /* ... (same 'p' case implementation as before)*/
            }
            else if (*format == 'r') {
                /* ... (same 'r' case implementation as before)*/
            }
            else if (*format == 'R') {
                /* ... (same 'R' case implementation as before)*/
            }
            else if (*format == '%') {
                /* ... (same '%' case implementation as before)*/
            }
        }
        else {
            print_to_buffer(buffer, &buffer_index, *format);
            char_count++;
        }

        format++;

        if (buffer_index >= BUFFER_SIZE)
            flush_buffer(buffer, &buffer_index);
    }

    /*Flush the remaining content in the buffer*/
    flush_buffer(buffer, &buffer_index);

    va_end(args);

    return char_count;
}

