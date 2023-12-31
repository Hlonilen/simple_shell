#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: assigned string containing history file
 */

char *get_history_file(info_val *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a new file or adds to an existing one
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_val *info)
{
	ssize_t val;
	char *filename = get_history_file(info);
	list_val *node = NULL;

	if (!filename)
		return (-1);

	val = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (val == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsval(node->cord, val);
		_putval('\n', val);
	}
	_putval(BUF_FLUSH, val);
	close(val);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_val *info)
{
	int valin, last = 0, linecount = 0;
	ssize_t val, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	val = open(filename, O_RDONLY);
	free(filename);
	if (val == -1)
		return (0);
	if (!fstat(val, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(val, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(val);
	for (valin = 0; valin < fsize; valin++)
		if (buf[valin] == '\n')
		{
			buf[valin] = 0;
			build_history_list(info, buf + last, linecount++);
			last = valin + 1;
		}
	if (last != valin)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure with potential arguments. used to keep things running
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_val *info, char *buf, int linecount)
{
	list_val *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Following updates, renumbers the history linked list
 * @info: Structure with potential arguments. used to keep things running
 *
 * Return: the new histcount
 */
int renumber_history(info_val *info)
{
	list_val *node = info->history;
	int valin = 0;

	while (node)
	{
		node->num = valin++;
		node = node->next;
	}
	return (info->histcount = valin);
}
