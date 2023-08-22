#include <stdio.h>
#include "shell.h"

/**
 * list_len - Write a program that determines length of linked list
 * @h: pointer
 *
 * Return: the size of the list
 */
size_t list_len(const list_val *h)
{
	size_t in = 0;

	while (h)
	{
		h = h->next;
		in++;
	}
	return (in);
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
	size_t in = list_len(head), on;
	char **strs;
	char *cord;

	if (!head || !in)
		return (NULL);
	strs = malloc(sizeof(char *) * (in + 1));
	if (!strs)
		return (NULL);
	for (in = 0; node; node = node->next, in++)
	{
		cord = malloc(_strlen(node->cord) + 1);
		if (!cord)
		{
			for (on = 0; on < in; on++)
				free(strs[on]);
			free(strs);
			return (NULL);
		}

		cord = _strcpy(cord, node->cord);
		strs[in] = cord;
	}
	cord[in] = '\0';
	return (strs);
}

/**
 * print_list - write a program that prints all elements of a list_val linked list
 * @h: pointer
 *
 * Return: the size of the list
 */
size_t print_list(const list_val *h)
{
	size_t in = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->cord ? h->cord : "(nil)");
		_puts("\n");
		h = h->next;
		in++;
	}
	return (in);
}

/**
 * node_starts_with - qrite a program that returns node whose string
 * starts with a prefix
 * @prefix: string
 * @node: pointer
 * @c: the character after the prefix to match
 *
 * Return: the node or null
 */
list_val *node_starts_with(list_val *node, char *prefix, char c)
{
	char *poin = NULL;

	while (node)
	{
		poin = starts_with(node->cord, prefix);
		if (poin && ((c == -1) || (*poin == c)))
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
	size_t in = 0;

	while (head)
	{
		if (head == node)
			return (in);
		head = head->next;
		in++;
	}
	return (-1);
}
