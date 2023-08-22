#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * *_memset - Write a program will fill the  memory with a constant byte
 * @valsum: the pointer to the memory area
 * @valnom: bytes amount
 * @valbin: the byte that will be used to fill *valsum
 *
 * Return: pointer *valsum
 */
char *_memset(char *valsum, char valbin, unsigned int valnom)
{
	unsigned int valin;

	for (valin = 0; valin < valnom; valin++)
		valsum[valin] = valbin;
	return (valsum);
}

/**
 * ffree - Write a function or peogram that will free a string off strings
 * @valpins: the string
 */
void ffree(char **valpins)
{
	char **valana = valpins;

	if (!valpins)
		return;
	while (*valpins)
		free(*valpins++);
	free(valana);
}

/**
 * _realloc - Write a function that will reallocate a block of memory
 * @new_size: new block size
 * @pota: pointer to old malloc'ated block
 * @old_size: old block size
 *
 * Return: pointer
 */
void *_realloc(void *pota, unsigned int old_size, unsigned int new_size)
{
	char *valpin;

	if (!pota)
		return (malloc(new_size));
	if (!new_size)
		return (free(pota), NULL);
	if (new_size == old_size)
		return (pota);
	valpin = malloc(new_size);
	if (!pota)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		valpin[old_size] = ((char *)pota)[old_size];

	free(pota);
	return (valpin);
}
