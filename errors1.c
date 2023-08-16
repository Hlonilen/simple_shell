#include "shell.h"

/**
 * _erratoi - translates a string to an integer
 * @valsum: the string that will be transformed
 * Return: If there are no numbers in the string, return 0; otherwise, return the converted number.
 *       -1 on error
 */
int _erratoi(char *valsum)
{
	int valin = 0;
	unsigned long int result = 0;

	if (*valsum == '+')
		valsum++;  /* TODO: why does this make main return 255? */
	for (valin = 0;  valsum[valin] != '\0'; valin++)
	{
		if (valsum[valin] >= '0' && valsum[valin] <= '9')
		{
			result *= 10;
			result += (valsum[valin] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - displays an error message
 * @info: the argument and return information struct
 * @estr: string with the error type provided
 * Return: If there are no numbers in the string, return 0; otherwise, return the converted number.
 *        -1 on error
 */
void print_error(info_val *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - The function returns a decimal (integer) number (in base 10)
 * @input: the input
 * @val: the file descriptor to which to write
 *
 * Return: amount of printed characters
 */
int print_d(int input, int val)
{
	int (*__putchar)(char) = _putchar;
	int valin, count = 0;
	unsigned int _abs_, current;

	if (val == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (valin = 1000000000; valin > 1; valin /= 10)
	{
		if (_abs_ / valin)
		{
			__putchar('0' + current / valin);
			count++;
		}
		current %= valin;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *pota;
	unsigned long valnom = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		valnom = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pota = &buffer[49];
	*pota = '\0';

	do	{
		*--pota = array[valnom % base];
		valnom /= base;
	} while (valnom != 0);

	if (sign)
		*--pota = sign;
	return (pota);
}

/**
 * remove_comments - function substitutes the first occurrence of '#' with '0'
 * @buf: address of the string to be changed
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int valin;

	for (valin = 0; buf[valin] != '\0'; valin++)
		if (buf[valin] == '#' && (!valin || buf[valin - 1] == ' '))
		{
			buf[valin] = '\0';
			break;
		}
}
