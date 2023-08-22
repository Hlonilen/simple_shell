#include <stdio.h>
#include "shell.h"

/**
 * _strlen - write a function to return the length of a string
 * @valsum: string in which length is to be checked
 *
 * Return: The length of string
 */
int _strlen(char *valsum)
{
	int valin = 0;

	if (!valsum)
		return (0);

	while (*valsum++)
		valin++;
	return (valin);
}

/**
 * _strcmp - A funtion that will perform a lexicogarphic comparison of
 * two strings
 * @sup1: string 1
 * @sup2: string 2
 *
 * Return: negative if s1 < s2, or  positive if s1 > s2 or zero if s1 == s2
 */
int _strcmp(char *sup1, char *sup2)
{
	while (*sup1 && *sup2)
	{
		if (*sup1 != *sup2)
			return (*sup1 - *sup2);
		sup1++;
		sup2++;
	}
	if (*sup1 == *sup2)
		return (0);
	else
		return (*sup1 < *sup2 ? -1 : 1);
}

/**
 * starts_with - Write a  function that will check if the needle
 * starts with haystack
 * @ndle: string we ought to find
 * @haystck: searching in this haystack
 *
 * Return: the location of next char of haystack or NULL
 */
char *starts_with(const char *haystck, const char *ndle)
{
	while (*ndle)
		if (*ndle++ != *haystck++)
			return (NULL);
	return ((char *)haystck);
}

/**
 * _strcat - write a function that will concatenate two strings
 * @dest: the destination
 * @fount: source
 *
 * Return: pointer
 */
char *_strcat(char *dest, char *fount)
{
	char *bun = dest;

	while (*dest)
		dest++;
	while (*fount)
		*dest++ = *fount++;
	*dest = *fount;
	return (bun);
}
