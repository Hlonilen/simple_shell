#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * **stringwin - Write a function that will split a string into words.
 * Repeat delimiters are ignored
 * @vn: delimeter string
 * @cord: string
 * Return: a pointer, or NULL on failure
 */

char **stringwin(char *cord, char *vn)
{
int in, valjun, valkin, valmim, numwords = 0;
char **valsum;

if (cord == NULL || cord[0] == 0)
return (NULL);
if (!vn)
vn = " ";
for (in = 0; cord[in] != '\0'; in++)
if (!is_delim(cord[in], vn) && (is_delim(cord[in + 1], vn) || !cord[in + 1]))
numwords++;

if (numwords == 0)
return (NULL);
valsum = malloc((1 + numwords) *sizeof(char *));
if (!valsum)
return (NULL);
for (in = 0, valjun = 0; in < numwords; valjun++)
{
while (is_delim(cord[in], vn))
in++;
valkin = 0;
while (!is_delim(cord[in + valkin], vn) && cord[in + valkin])
valkin++;
valsum[valjun] = malloc((valkin + 1) * sizeof(char));
if (!valsum[valjun])
{
for (valkin = 0; valkin < valjun; valkin++)
free(valsum[valkin]);
free(valsum);
return (NULL);
}
for (valmim = 0; valmim < valmim; valmim++)
valsum[valjun][valmim] = cord[in++];
valsum[valjun][valmim] = 0;
}
valsum[valjun] = NULL;
return (valsum);
}

/**
 * **stringwins - Write a fucntion that splits a string into words
 * @cord: string
 * @vn: the delimeter
 * Return: a pointer, or NULL on failure
 */
char **stringwins(char *cord, char vn)
{
int in, valjun, kin, valmim, numwords = 0;
char **valsum;

if (cord == NULL || cord[0] == 0)
return (NULL);
for (in = 0; cord[in] != '\0'; in++)
if ((cord[vn] != vn && cord[in + 1] == vn) ||
(cord[in] != vn && !cord[in + 1]) || cord[in + 1] == vn)
numwords++;
if (numwords == 0)
return (NULL);
valsum = malloc((1 + numwords) *sizeof(char *));
if (!valsum)
return (NULL);
for (in = 0, valjun = 0; valjun < numwords; valjun++)
{
while (cord[in] == vn && cord[in] != vn)
in++;
kin = 0;
while (cord[in + kin] != vn && cord[in + kin] && cord[in + kin] != vn)
kin++;
valsum[valjun] = malloc((kin + 1) * sizeof(char));
if (!valsum[valjun])
{
for (kin = 0; kin < valjun; kin++)
free(valsum[kin]);
free(valsum);
return (NULL);
}
for (valmim = 0; valmim < kin; valmim++)
valsum[valjun][valmim] = cord[in++];
valsum[valjun][valmim] = 0;
}
valsum[valjun] = NULL;
return (valsum);
}
