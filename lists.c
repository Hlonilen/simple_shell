#include "shell.h"

/**
 * add_node - adds a node to the list's beginning
 * @head: address of the reference to the head node
 * @cord: cord field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_val *add_node(list_val **head, const char *cord, int num)
{
	list_val *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_val));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_val));
	new_head->num = num;
	if (cord)
	{
		new_head->cord = _strdup(cord);
		if (!new_head->cord)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of the reference to the head node
 * @cord: cord field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_val *add_node_end(list_val **head, const char *cord, int num)
{
	list_val *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_val));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_val));
	new_node->num = num;
	if (cord)
	{
		new_node->cord = _strdup(cord);
		if (!new_node->cord)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - Only the str element of a list_val linked list is printed.
 * @valhun: a reference to the first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_val *valhun)
{
	size_t valin = 0;

	while (valhun)
	{
		_puts(valhun->cord ? valhun->cord : "(nil)");
		_puts("\n");
		valhun = valhun->next;
		valin++;
	}
	return (valin);
}

/**
 * delete_node_at_index - deletes the node at the specified index
 * @head: address of the initial node's pointer
 * @index: node index to remove
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_val **head, unsigned int index)
{
	list_val *node, *prev_node;
	unsigned int valin = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->cord);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (valin == index)
		{
			prev_node->next = node->next;
			free(node->cord);
			free(node);
			return (1);
		}
		valin++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @headpota: address of the reference to the head node
 *
 * Return: void
 */
void free_list(list_val **headpota)
{
	list_val *node, *next_node, *head;

	if (!headpota || !*headpota)
		return;
	head = *headpota;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->cord);
		free(node);
		node = next_node;
	}
	*headpota = NULL;
}
