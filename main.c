#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * main - starting point
 * @avent: argument vector
 * @acent: argument count
 *
 * Return: 0 on success, 1 on error
 */
int main(int acent, char **avent)
{
	info_val info[] = { INFO_INIT };
	int val = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (val)
			: "r" (val));

	if (acent == 2)
	{
		val = open(avent[1], O_RDONLY);
		if (val == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(avent[0]);
				_eputs(": 0: Can't open ");
				_eputs(avent[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readval = val;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, avent);
	return (EXIT_SUCCESS);
}
