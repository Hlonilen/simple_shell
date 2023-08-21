#include "shell.h"

/**
 * interactive - If the shell is in interactive mode, this function returns true.
 * @info: struct address
 * Return: If in interactive mode, 1; otherwise, 0.
 */
int interactive(info_val *info)
{
        return (isatty(STDIN_FILENO) && info->readval <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @valcum: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char valcum, char *delim)
{
        while (*delim)
                if (*delim++ == valcum)
                        return (1);
        return (0);
}

/**
 * _isalpha - checks for the presence of an alphabetic character
 * @valcum: The input character
 * Return: If valcum is alphabetical, 1 is returned; otherwise, 0 is returned.
 */

int _isalpha(int valcum)
{
        if ((valcum >= 'a' && valcum <= 'z') || (valcum >= 'A' && valcum <= 'Z'))
                return (1);
        else
                return (0);
}
/**
 * _atoi - transforms a string to an integer
 * @valsum: the string that will be transformed
 * Return: If there are no numbers in the string, return 0; otherwise, return the converted number.
 */

int _atoi(char *valsum)
{
        int valin, sign = 1, flag = 0, output;
        unsigned int result = 0;

        for (valin = 0; valsum[valin] != '\0' && flag != 2; valin++)
        {
                if (valsum[valin] == '-')
                        sign *= -1;

                if (valsum[valin] >= '0' && valsum[valin] <= '9')
                {
                        flag = 1;
                        result *= 10;
                        result += (valsum[valin] - '0');
                }
                else if (flag == 1)
                        flag = 2;
        }

        if (sign == -1)
                output = -result;
        else
                output = result;

        return (output);
}
