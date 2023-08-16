#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * **strtow - Write a function that will split a string into words.
 * Repeat delimiters are ignored
 * @d: delimeter string
 * @str: string
 * Return: a pointer, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int a, b, c, e, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (is_delim(str[a], d))
			a++;
		c = 0;
		while (!is_delim(str[a + c], d) && str[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < c; e++)
			s[b][e] = str[a++];
		s[b][e] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **strtow2 - Write a fucntion that splits a string into words
 * @str: string
 * @d: the delimeter
 * Return: a pointer, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int w, x, y, z, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (w = 0; str[w] != '\0'; w++)
		if ((str[w] != d && str[w + 1] == d) ||
		    (str[w] != d && !str[w + 1]) || str[w + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (w = 0, x = 0; x < numwords; x++)
	{
		while (str[w] == d && str[w] != d)
			w++;
		y = 0;
		while (str[w + y] != d && str[w + y] && str[w + y] != d)
			y++;
		s[x] = malloc((y + 1) * sizeof(char));
		if (!s[x])
		{
			for (y = 0; y < x; y++)
				free(s[y]);
			free(s);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			s[x][z] = str[w++];
		s[x][z] = 0;
	}
	s[x] = NULL;
	return (s);
}
