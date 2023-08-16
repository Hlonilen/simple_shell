#include "shell.h"

/**
 * _myhistory - shows the history list, one command at a time, followed by
 *              with line numbers beginning at 0.
 * @info: Structure with potential arguments. used to keep things running
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_val *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @cord: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_val *info, char *cord)
{
	char *valpin, valcum;
	int bun;

	valpin = _strchr(cord, '=');
	if (!valpin)
		return (1);
	valcum = *valpin;
	*valpin = 0;
	bun = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, cord, -1)));
	*valpin = valcum;
	return (bun);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @cord: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_val *info, char *cord)
{
	char *valpin;

	valpin = _strchr(cord, '=');
	if (!valpin)
		return (1);
	if (!*++valpin)
		return (unset_alias(info, cord));

	unset_alias(info, cord);
	return (add_node_end(&(info->alias), cord, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_val *node)
{
	char *valpin = NULL, *valana = NULL;

	if (node)
	{
		valpin = _strchr(node->cord, '=');
		for (valana = node->cord; valana <= valpin; valana++)
		_putchar(*valana);
		_putchar('\'');
		_puts(valpin + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure holding potential arguments. used to keep
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_val *info)
{
	int valin = 0;
	char *valpin = NULL;
	list_val *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (valin = 1; info->argv[valin]; valin++)
	{
		valpin = _strchr(info->argv[valin], '=');
		if (valpin)
			set_alias(info, info->argv[valin]);
		else
			print_alias(node_starts_with(info->alias, info->argv[valin], '='));
	}

	return (0);
}
