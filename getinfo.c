#include "shell.h"

/**
 * clear_info - initializes info_val struct
 * @info: struct address
 */
void clear_info(info_val *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_val struct
 * @info: struct address
 * @avent: argument vector
 */
void set_info(info_val *info, char **avent)
{
	int valin = 0;

	info->fname = avent[0];
	if (info->arg)
	{
		info->argv = stringwin(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (valin = 0; info->argv && info->argv[valin]; valin++)
			;
		info->argc = valin;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - frees info_val struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_val *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readval > 2)
			close(info->readval);
		_putchar(BUF_FLUSH);
	}
}
