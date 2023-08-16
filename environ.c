#include "shell.h"

/**
 * _myenv - the current environment is printed
 * @info: Structure with potential arguments. used to keep things running
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_val *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - obtains the value of an environ variable
 * @info: Structure with potential arguments. used to keep things running
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_val *info, const char *name)
{
	list_val *node = info->env;
	char *valpin;

	while (node)
	{
		valpin = starts_with(node->cord, name);
		if (valpin && *valpin)
			return (valpin);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or change an existing one
 * @info: Structure with potential arguments. used to keep things running
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_val *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure with potential arguments. used to keep things running
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_val *info)
{
	int valin;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (valin = 1; valin <= info->argc; valin++)
		_unsetenv(info, info->argv[valin]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure with potential arguments. used to keep things running
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_val *info)
{
	list_val *node = NULL;
	size_t valin;

	for (valin = 0; environ[valin]; valin++)
		add_node_end(&node, environ[valin], 0);
	info->env = node;
	return (0);
}
