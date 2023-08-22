#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

/**
 * is_cmd - Write a program that will determine if a file is an
 * executable command
 * @path: the path to the file
 * @info: info
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_val *info, char *path)
{
	struct stat sting;

	(void)info;
	if (!path || stat(path, &sting))
		return (0);

	if (sting.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - write a program that duplicates characters
 * @stop: the index to stop duplicating
 * @pathcord: Path str
 * @start: index to start
 *
 * Return: new buffer
 */
char *dup_chars(char *pathcord, int start, int stop)
{
	static char buf[1024];
	int valin = 0, valkin = 0;

	for (valkin = 0, valin = start; valin < stop; valin++)
		if (pathcord[valin] != ':')
			buf[valkin++] = pathcord[valin];
	buf[valkin] = 0;
	return (buf);
}

/**
 * find_path - Write program that finds this cmd in the PATH string
 * @cmd: The cmd file to find
 * @pathcord: the PATH string
 * @info: info
 *
 * Return: NULL
 */
char *find_path(info_val *info, char *pathcord, char *cmd)
{
	int valin = 0, curr_post = 0;
	char *path;

	if (!pathcord)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathcord[valin] || pathcord[valin] == ':')
		{
			path = dup_chars(pathcord, curr_post, valin);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathcord[valin])
				break;
			curr_post = valin;
		}
		valin++;
	}
	return (NULL);
}
