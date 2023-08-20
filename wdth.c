#include "main.h"

/**
 * get_width - Calculates the width for printing
 * by mukiux featuring cynthiaimari
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: wdth.
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr_i;
	int wdth = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			wdth *= 10;
			wdth += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			wdth = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (wdth);
}