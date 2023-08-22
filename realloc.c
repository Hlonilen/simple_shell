#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * *_memset - Write a program will fill the  memory with a constant byte
 * @s: the pointer to the memory area
 * @n: bytes amount
 * @b: the byte that will be used to fill *s
 *
 * Return: pointer *s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int in;

	for (in = 0; in < n; in++)
		s[in] = b;
	return (s);
}

/**
 * ffree - Write a function or peogram that will free a string off strings
 * @pp: string
 */
void ffree(char **pp)
{
	char **in = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(in);
}

/**
 * _realloc - Write a function that will reallocate a block of memory
 * @new_size: new block size
 * @ptr: pointer to old malloc'ated block
 * @old_size: old block size
 *
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *poin;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	poin = malloc(new_size);
	if (!poin)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		poin[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return (poin);
}
