#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * bfree - write a program that frees a pointer and NULLs the address
 * @pota: the address of the pointer to freed
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **pota)
{
	if (pota && *pota)
	{
		free(*pota);
		*pota = NULL;
		return (1);
	}
	return (0);
}
