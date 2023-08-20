#include "main.h"

/**
 * get_prcsn - Calculates the precision for printing
 * by mukiux featuring cynthiaimari
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Prcsn.
 */
int get_prcsn(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int prcsn = -1;

	if (format[curr_i] != '.')
		return (prcsn);

	prcsn = 0;

	for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			prcsn *= 10;
			prcsn += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			prcsn = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (prcsn);
}
