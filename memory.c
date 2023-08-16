#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * bfree - write a program that frees a pointer and NULLs the address
 * @ptr: the address of the pointer to freed
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
