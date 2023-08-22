#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * is_chain - Write a fucntion that will test if the current
 * char in buffer is a chain delimeter
 * @info: info struct and parameter
 * @buf: buffer character
 * @valpin: current location in buf
 * Return: 1 if chain delimeter, otherwise 0
 */
int is_chain(info_val *info, char *buf, size_t *valpin)
{
	size_t valjun = *valpin;

	if (buf[valjun] == '|' && buf[valjun + 1] == '|')
	{
		buf[valjun] = 0;
		valjun++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[valjun] == '&' && buf[valjun + 1] == '&')
	{
		buf[valjun] = 0;
		valjun++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[valjun] == ';') /* at the end of this command */
	{
		buf[valjun] = 0; /* will replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*valpin = valjun;
	return (1);
}

/**
 * check_chain - A function that will check if we should continue chaining
 * based on last status
 * @valin: initial position
 * @valpin: location of present position in buffer
 * @info: info struct and the parameter
 * @buf: buffer character
 * @len: length of buffer
 *
 * Return: nothing
 */
void check_chain(info_val *info, char *buf, size_t *valpin, size_t valin, size_t len)
{
	size_t valjun = *valpin;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[valin] = 0;
			valjun = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[valin] = 0;
			valjun = len;
		}
	}

	*valpin = valjun;
}

/**
 * replace_alias - a function will replace aliases in the tokenized string
 * @info: info struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_val *info)
{
	int valin;
	list_val *node;
	char *valpin;

	for (valin = 0; valin < 10; valin++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		valpin = _strchr(node->cord, '=');
		if (!valpin)
			return (0);
		valpin = _strdup(valpin + 1);
		if (!valpin)
			return (0);
		info->argv[0] = valpin;
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
	int valin = 0;
	list_val *node;

	for (valin = 0; info->argv[valin]; valin++)
	{
		if (info->argv[valin][0] != '$' || !info->argv[valin][1])
			continue;

		if (!_strcmp(info->argv[valin], "$?"))
		{
			replace_string(&(info->argv[valin]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[valin], "$$"))
		{
			replace_string(&(info->argv[valin]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[valin][1], '=');
		if (node)
		{
			replace_string(&(info->argv[valin]),
				_strdup(_strchr(node->cord, '=') + 1));
			continue;
		}
		replace_string(&info->argv[valin], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - a function to replace the string
 * @former: address of previous string
 * @brandnew: current string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **former, char *brandnew)
{
	free(*former);
	*former = brandnew;
	return (1);
}
