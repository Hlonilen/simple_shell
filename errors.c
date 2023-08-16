#include "shell.h"

/**
 * _eputs - outputs an input string
 * @cord: the string that will be printed
 *
 * Return: Nothing
 */
void _eputs(char *cord)
{
	int valin = 0;

	if (!cord)
		return;
	while (cord[valin] != '\0')
	{
		_eputchar(cord[valin]);
		valin++;
	}
}

/**
 * _eputchar - stderr is where the character valcum is written.
 * @valcum: The character to print
 *
 * Return: On success 1.
 * In the event of an error, -1 is returned and errno is set properly.
 */
int _eputchar(char valcum)
{
	static int valin;
	static char buf[WRITE_BUF_SIZE];

	if (valcum == BUF_FLUSH || valin >= WRITE_BUF_SIZE)
	{
		write(2, buf, valin);
		valin = 0;
	}
	if (valcum != BUF_FLUSH)
		buf[valin++] = valcum;
	return (1);
}

/**
 * _putval - translates the character valcum to the supplied val
 * @valcum: The character to output
 * @val: The file descriptor to which to write
 *
 * Return: On success 1.
 * In the event of an error, -1 is returned and errno is set properly.
 */
int _putval(char valcum, int val)
{
	static int valin;
	static char buf[WRITE_BUF_SIZE];

	if (valcum == BUF_FLUSH || valin >= WRITE_BUF_SIZE)
	{
		write(val, buf, valin);
		valin = 0;
	}
	if (valcum != BUF_FLUSH)
		buf[valin++] = valcum;
	return (1);
}

/**
 * _putsval - outputs an input string
 * @cord: the string that will be printed
 * @val: the file descriptor to which to write
 *
 * Return: the number of characters entered
 */
int _putsval(char *cord, int val)
{
	int valin = 0;

	if (!cord)
		return (0);
	while (*cord)
	{
		valin += _putval(*cord++, val);
	}
	return (valin);
}
