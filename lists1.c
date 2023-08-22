#include <stdio.h>
#include "shell.h"

/**
 * list_len - Write a program that determines length of linked list
 * @valhun: pointer
 *
 * Return: the size of the list
 */
size_t list_len(const list_val *valhun)
{
	size_t valin = 0;

	while (valhun)
	{
		valhun = valhun->next;
		valin++;
	}
	return (valin);
}

/**
 * list_to_strings - a program that returns an array of strings of the list
 * @head: the pointer
 *
 * Return: an array of strings
 */
char **list_to_strings(list_val *head)
{
	list_val *node = head;
	size_t valin = list_len(head), valjun;
	char **cords;
	char *cord;

	if (!head || !valin)
		return (NULL);
	cords = malloc(sizeof(char *) * (valin + 1));
	if (!cords)
		return (NULL);
	for (valin = 0; node; node = node->next, valin++)
	{
		cord = malloc(_strlen(node->cord) + 1);
		if (!cord)
		{
			for (valjun = 0; valjun < valin; valjun++)
				free(cords[valjun]);
			free(cords);
			return (NULL);
		}

		cord = _strcpy(cord, node->cord);
		cords[valin] = cord;
	}
	cords[valin] = NULL;
	return (cords);
}
/**
 * print_list - write a program that prints all elements of a list_val
 * linked list
 * @valhun: pointer
 *
 * Return: the size of the list
 */
size_t print_list(const list_val *valhun)
{
	size_t valin = 0;

	while (valhun)
	{
		_puts(convert_number(valhun->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(valhun->cord ? valhun->cord : "(nil)");
		_puts("\n");
		valhun = valhun->next;
		valin++;
	}
	return (valin);
}

/**
 * node_starts_with - qrite a program that returns node whose string
 * starts with a prefix
 * @prefix: string
 * @node: pointer
 * @valcum: the character after the prefix to match
 *
 * Return: the node or null
 */
list_val *node_starts_with(list_val *node, char *prefix, char valcum)
{
	char *valpin = NULL;

	while (node)
	{
		valpin = starts_with(node->cord, prefix);
		if (valpin && ((valcum == -1) || (*valpin == valcum)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - write a program that gets the index of a node
 * @node: point to 1
 * @head: pointer 2
 *
 * Return: node or -1
 */
ssize_t get_node_index(list_val *head, list_val *node)
{
	size_t valin = 0;

	while (head)
	{
		if (head == node)
			return (valin);
		head = head->next;
		valin++;
	}
	return (-1);
}
