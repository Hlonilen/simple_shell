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
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - write a program that duplicates characters
 * @stop: the index to stop duplicating
 * @pathstr: Path str
 * @start: index to start
 *
 * Return: new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int in = 0, on = 0;

	for (on = 0, in = start; in < stop; in++)
		if (pathstr[in] != ':')
			buf[on++] = pathstr[in];
	buf[on] = 0;
	return (buf);
}

/**
 * find_path - Write program that finds this cmd in the PATH string
 * @cmd: The cmd file to find
 * @pathstr: the PATH string
 * @info: info
 *
 * Return: NULL
 */
char *find_path(info_val *info, char *pathstr, char *cmd)
{
	int in = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[in] || pathstr[in] == ':')
		{
			path = dup_chars(pathstr, curr_pos, in);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[in])
				break;
			curr_pos = in;
		}
		in++;
	}
	return (NULL);
}
