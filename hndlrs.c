#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * by mukiux featuring cynthiaimari
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flgs:  Calculates active flags.
 * @wdth: get width.
 * @prcsn: precision specifier
 * @sz: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
	int flgs, int wdth, int prcsn, int sz)
{ /* char is stored at left and paddind at buffer's right */
	int i = 0;
	char padd = ' ';

	UNUSED(prcsn);
	UNUSED(sz);

	if (flgs & F_ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (wdth > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < wdth - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		if (flgs & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], wdth - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], wdth - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @buffer: Buffer array to handle print
 * @flgs:  Calculates active flags
 * @wdth: get width.
 * @prcsn: precision specifier
 * @sz: Size specifier
 * by mukiux featuring cynthiaimari
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flgs, int wdth, int prcsn, int sz)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(sz);

	if ((flgs & F_ZERO) && !(flgs & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flgs & F_PLUS)
		extra_ch = '+';
	else if (flgs & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flgs, wdth, prcsn,
		length, padd, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flgs: Flags
 * @wdth: width
 * @prcsn: Precision specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 * by mukiux featuring cythiaimari
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
	int flgs, int wdth, int prcsn,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prcsn == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && wdth == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prcsn == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prcsn > 0 && prcsn < length)
		padd = ' ';
	while (prcsn > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (wdth > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flgs & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flgs & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flgs & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flgs: Flags specifiers
 * @wdth: Width specifier
 * @prcsn: Precision specifier
 * @sz: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flgs, int wdth, int prcsn, int sz)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(sz);

	if (prcsn == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (prcsn > 0 && prcsn < length)
		padd = ' ';

	while (prcsn > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flgs & F_ZERO) && !(flgs & F_MINUS))
		padd = '0';

	if (wdth > length)
	{
		for (i = 0; i < wdth - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flgs & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @wdth: Wdth specifier
 * @flgs: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 * by mukiux featuring cynthiaimari
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
	int wdth, int flgs, char padd, char extra_c, int padd_start)
{
	int i;

	if (wdth > length)
	{
		for (i = 3; i < wdth - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flgs & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flgs & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flgs & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
