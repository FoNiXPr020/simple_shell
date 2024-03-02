#include "shell.h"

/**
 * determine_list_length - Determine the length of a linked list.
 * @h: Pointer to the first node.
 * Return: Size of the list.
 */
size_t determine_list_length(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * convert_list_to_strings - Convert a linked list to an array of strings.
 * @head: Pointer to the first node.
 * Return: Array of strings.
 */
char **convert_list_to_strings(list_t *head)
{
	list_t *iNode = head;
	size_t i = determine_list_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; iNode; iNode = iNode->next, i++)
	{
		str = malloc(_string_length(iNode->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, iNode->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * display_list - Print all elements of a list_t linked list.
 * @h: Pointer to the first node.
 * Return: Size of the list.
 */
size_t display_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(number_conversion(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * find_node_with_prefix - Return the node
 * whose string starts with a given prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after prefix to match.
 * Return: Matching node or NULL.
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = check_prefix(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * obtain_node_index - Obtain the index of a node.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 * Return: Index of the node or -1.
 */
ssize_t obtain_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

