#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * _strlen - write a function to return the length of a string
 * @s: string in which length is to be checked
 *
 * Return: The length of string
 */
int _strlen(char *s)
{
	int in = 0;

	if (!s)
		return (0);

	while (*s++)
		in++;
	return (in);
}

/**
 * _strcmp - A funtion that will perform a lexicogarphic comparison of
 * two strings
 * @s1: string 1
 * @s2: string 2
 *
 * Return: negative if s1 < s2, or  positive if s1 > s2 or zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Write a  function that will check if the needle
 * starts with haystack
 * @needle: string we ought to find
 * @haystack: searching in this haystack
 *
 * Return: the location of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - write a function that will concatenate two strings
 * @dest: the destination
 * @src: source
 *
 * Return: pointer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
