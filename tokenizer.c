#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * **strtow - Write a function that will split a string into words.
 * Repeat delimiters are ignored
 * @d: delimeter string
 * @cord: string
 * Return: a pointer, or NULL on failure
 */

char **strtow(char *cord, char *d)
{
	int in, on, c, e, numwords = 0;
	char **s;

	if (cord == NULL || cord[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (in = 0; cord[in] != '\0'; in++)
		if (!is_delim(cord[in], d) && (is_delim(cord[in + 1], d) || !cord[in + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (in = 0, on = 0; on < numwords; on++)
	{
		while (is_delim(cord[in], d))
			in++;
		c = 0;
		while (!is_delim(cord[in + c], d) && cord[in + c])
			c++;
		s[on] = malloc((c + 1) * sizeof(char));
		if (!s[on])
		{
			for (c = 0; c < on; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < c; e++)
			s[on][e] = cord[in++];
		s[on][e] = 0;
	}
	s[on] = NULL;
	return (s);
}

/**
 * **strtow2 - Write a fucntion that splits a string into words
 * @cord: string
 * @d: the delimeter
 * Return: a pointer, or NULL on failure
 */
char **strtow2(char *cord, char d)
{
	int w, x, y, z, numwords = 0;
	char **s;

	if (cord == NULL || cord[0] == 0)
		return (NULL);
	for (w = 0; cord[w] != '\0'; w++)
		if ((cord[w] != d && cord[w + 1] == d) ||
		    (cord[w] != d && !cord[w + 1]) || cord[w + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (w = 0, x = 0; x < numwords; x++)
	{
		while (cord[w] == d && cord[w] != d)
			w++;
		y = 0;
		while (cord[w + y] != d && cord[w + y] && cord[w + y] != d)
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
			s[x][z] = cord[w++];
		s[x][z] = 0;
	}
	s[x] = NULL;
	return (s);
}
