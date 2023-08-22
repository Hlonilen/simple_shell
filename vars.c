#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * is_chain - Write a fucntion that will test if the current
 * char in buffer is a chain delimeter
 * @info: info struct and parameter
 * @buf: buffer character
 * @p: the location/address of current position in buffer
 *
 * Return: 1 if chain delimeter, otherwise 0
 */
int is_chain(info_val *info, char *buf, size_t *p)
{
	size_t of = *p;

	if (buf[of] == '|' && buf[of + 1] == '|')
	{
		buf[of] = 0;
		of++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[of] == '&' && buf[of + 1] == '&')
	{
		buf[of] = 0;
		of++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[of] == ';') /* at the end of this command */
	{
		buf[of] = 0; /* will replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = of;
	return (1);
}

/**
 * check_chain - A function that will check if we should continue chaining
 * based on last status
 * @i: initial position
 * @p: location of present position in buffer
 * @info: info struct and the parameter
 * @buf: buffer character
 * @len: length of buffer
 *
 * Return: nothing
 */
void check_chain(info_val *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t of = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			of = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			of = len;
		}
	}

	*p = of;
}

/**
 * replace_alias - a function will replace aliases in the tokenized string
 * @info: info struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_val *info)
{
	int in;
	list_val *node;
	char *poin;

	for (in = 0; in < 10; in++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		poin = _strchr(node->cord, '=');
		if (!poin)
			return (0);
		poin = _strdup(poin + 1);
		if (!poin)
			return (0);
		info->argv[0] = poin;
	}
	return (1);
}

/**
 * replace_vars - a function that will replace vars in the tokenized string
 * @info: struct info
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_val *info)
{
	int in = 0;
	list_val *node;

	for (in = 0; info->argv[in]; in++)
	{
		if (info->argv[in][0] != '$' || !info->argv[in][1])
			continue;

		if (!_strcmp(info->argv[in], "$?"))
		{
			replace_string(&(info->argv[in]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[in], "$$"))
		{
			replace_string(&(info->argv[in]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[in][1], '=');
		if (node)
		{
			replace_string(&(info->argv[in]),
				_strdup(_strchr(node->cord, '=') + 1));
			continue;
		}
		replace_string(&info->argv[in], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - a function to replace the string
 * @old: address of previous string
 * @new: current string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
