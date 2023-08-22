#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * main - starting point
 * @av: argument vector
 * @ac: argument count
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_val info[] = { INFO_INIT };
	int val = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (val)
		: "r" (val));

	if (ac == 2)
	{
		val = open(av[1], O_RDONLY);
		if (val == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
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
	hsh(info, av);
	return (EXIT_SUCCESS);
}
