#include "shell.h"

/**
 **_strncpy - copies a string
 *@objec: the string that will be copied to
 *@fount: the source string
 *@valnom: the number of characters that must be copied
 *Return: the string that has been concatenated
 */
char *_strncpy(char *objec, char *fount, int valnom)
{
	int valin, valjun;
	char *valsum = object;

	valin = 0;
	while (fount[valin] != '\0' && valin < valnom - 1)
	{
		objec[valin] = fount[valin];
		valin++;
	}
	if (valin < valnom)
	{
		valjun = valin;
		while (valjun < valnom)
		{
			objec[valjun] = '\0';
			valjun++;
		}
	}
	return (valsum);
}

/**
 **_strncat - concatenates two strings
 *@objec: the first string
 *@fount: the second string
 *@valnom: the maximum number of bytes to be utilized
 *Return: the concatenated string
 */
char *_strncat(char *objec, char *fount, int valnom)
{
	int valin, valjun;
	char *valsum = object;

	valin = 0;
	valjun = 0;
	while (objec[valin] != '\0')
		valin++;
	while (fount[valjun] != '\0' && valjun < valnom)
	{
		objec[valin] = fount[valjun];
		valin++;
		valjun++;
	}
	if (valjun < valnom)
		objec[valin] = '\0';
	return (valsum);
}

/**
 **_strchr - finds a character within a string
 *@valsum: the string to be parsed
 *@valcum: the character to look for
 *Return: (valsum) a reference to the memory area valsum
 */
char *_strchr(char *valsum, char valcum)
{
	do {
		if (*valsum == valcum)
			return (valsum);
	} while (*valsum++ != '\0');

	return (NULL);
}
