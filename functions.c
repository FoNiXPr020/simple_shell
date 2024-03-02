#include "shell.h"

/**
 * prepend_node - Add a node to the start of the list.
 * @head: Address of pointer to the head node.
 * @str: String field of the node.
 * @num: Node index used by history.
 * Return: Size of the list.
 */
list_t *prepend_node(list_t **head, const char *str, int num)
{
	list_t *iNew;

	if (!head)
		return (NULL);
	iNew = malloc(sizeof(list_t));
	if (!iNew)
		return (NULL);
	_fill_memory((void *)iNew, 0, sizeof(list_t));
	iNew->num = num;
	if (str)
	{
		iNew->str = _strdup(str);
		if (!iNew->str)
		{
			free(iNew);
			return (NULL);
		}
	}
	iNew->next = *head;
	*head = iNew;
	return (iNew);
}

/**
 * append_node - Add a node to the end of the list.
 * @head: Address of pointer to the head node.
 * @str: String field of the node.
 * @num: Node index used by history.
 * Return: Size of the list.
 */
list_t *append_node(list_t **head, const char *str, int num)
{
	list_t *new_node, *iNode;

	if (!head)
		return (NULL);

	iNode = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_fill_memory((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (iNode)
	{
		while (iNode->next)
			iNode = iNode->next;
		iNode->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_string_list - Print only the string element of a list_t linked list.
 * @h: Pointer to the first node.
 * Return: Size of the list.
 */
size_t print_string_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * remove_node_at_index - Delete a node at the given index.
 * @head: Address of pointer to the first node.
 * @index: Index of the node to delete.
 * Return: 1 on success, 0 on failure.
 */
int remove_node_at_index(list_t **head, unsigned int index)
{
	list_t *iNode, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		iNode = *head;
		*head = (*head)->next;
		free(iNode->str);
		free(iNode);
		return (1);
	}
	iNode = *head;
	while (iNode)
	{
		if (i == index)
		{
			prev_node->next = iNode->next;
			free(iNode->str);
			free(iNode);
			return (1);
		}
		i++;
		prev_node = iNode;
		iNode = iNode->next;
	}
	return (0);
}

/**
 * deallocate_list - Free all nodes of a list.
 * @head_ptr: Address of pointer to the head node.
 * Return: Void.
 */
void deallocate_list(list_t **head_ptr)
{
	list_t *iNode, *next_iNode, *ihead;

	if (!head_ptr || !*head_ptr)
		return;
	ihead = *head_ptr;
	iNode = ihead;
	while (iNode)
	{
		next_iNode = iNode->next;
		free(iNode->str);
		free(iNode);
		iNode = next_iNode;
	}
	*head_ptr = NULL;
}

