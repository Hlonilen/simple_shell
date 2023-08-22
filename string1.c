#include <stdio.h>
#include "shell.h"

/**
 * _strcpy - A function that will copy a string
 * @fount: source
 * @dest: the destination
 *
 * Return: pointer
 */
char *_strcpy(char *dest, char *fount)
{
	int valin = 0;

	if (dest == fount || fount == 0)
		return (dest);
	while (fount[valin])
	{
		dest[valin] = fount[valin];
		valin++;
	}
	dest[valin] = 0;
	return (dest);
}

/**
 * _strdup - Write a function that will duplicate a string
 * @cord: the string
 *
 * Return: pointer
 */
char *_strdup(const char *cord)
{
	int len = 0;
	char *bun;

	if (cord == NULL)
		return (NULL);
	while (*cord++)
		len++;
	bun = malloc(sizeof(char) * (len + 1));
	if (!bun)
		return (NULL);
	for (len++; len--;)
		bun[len] = *--cord;
	return (bun);
}

/**
 *_puts - Write a function that will print an input string
 *@cord: the string
 *
 * Return: 0 always
 */
void _puts(char *cord)
{
	int valin = 0;

	if (!cord)
		return;
	while (cord[valin] != '\0')
	{
		_putchar(cord[valin]);
		valin++;
	}
}

/**
 * _putchar - A function that will write the character c to stdout
 * @valcum: The character
 *
 * Return: On success 1. On error -1
 * is returned, and errno is set
 */
int _putchar(char valcum)
{
	static int valin;
	static char buf[WRITE_BUF_SIZE];

	if (valcum == BUF_FLUSH || valin >= WRITE_BUF_SIZE)
	{
		write(1, buf, valin);
		valin = 0;
	}
	if (valcum != BUF_FLUSH)
		buf[valin++] = valcum;
	return (1);
}
