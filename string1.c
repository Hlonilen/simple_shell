#include <stdio.h>
#include "shell.h"

/**
 * _strcpy - A function that will copy a string
 * @src: source
 * @dest: the destination
 *
 * Return: pointer
 */
char *_strcpy(char *dest, char *src)
{
	int in = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[in])
	{
		dest[in] = src[in];
		in++;
	}
	dest[in] = 0;
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
	char *ret;

	if (cord == NULL)
		return (NULL);
	while (*cord++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--cord;
	return (ret);
}

/**
 *_puts - Write a function that will print an input string
 *@cord: the string
 *
 * Return: 0 always
 */
void _puts(char *cord)
{
	int in = 0;

	if (!cord)
		return;
	while (cord[in] != '\0')
	{
		_putchar(cord[in]);
		in++;
	}
}

/**
 * _putchar - A function that will write the character c to stdout
 * @c: The character
 *
 * Return: On success 1. On error -1
 * is returned, and errno is set
 */
int _putchar(char c)
{
	static int in;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || in >= WRITE_BUF_SIZE)
	{
		write(1, buf, in);
		in = 0;
	}
	if (c != BUF_FLUSH)
		buf[in++] = c;
	return (1);
}
