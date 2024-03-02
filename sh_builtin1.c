#include "shell.h"

/**
 * _display_history - Displays the history list,
 * one command per line, preceded
 * with line numbers starting at 0.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */

int _display_history(info_t *info)
{
	display_list(info->history);
	return (0);
}

/**
 * unset_shell_alias - Unsets an alias.
 * @info: Parameter struct.
 * @str: The string alias.
 * Return: Always 0 on success, 1 on error.
 */
int unset_shell_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _find_character(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = remove_node_at_index(&(info->alias),
		obtain_node_index(info->alias, find_node_with_prefix(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_shell_alias - Sets an alias to a string.
 * @info: Parameter struct.
 * @str: The string alias.
 * Return: Always 0 on success, 1 on error.
 */
int set_shell_alias(info_t *info, char *str)
{
	char *p;

	p = _find_character(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_shell_alias(info, str));

	unset_shell_alias(info, str);
	return (append_node(&(info->alias), str, 0) == NULL);
}

/**
 * print_shell_alias - Prints an alias string.
 * @node: The alias node.
 * Return: Always 0 on success, 1 on error.
 */
int print_shell_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _find_character(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _handle_shell_alias - Mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _handle_shell_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_shell_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _find_character(info->argv[i], '=');
		if (p)
			set_shell_alias(info, info->argv[i]);
		else
			print_shell_alias(find_node_with_prefix(info->alias, info->argv[i], '='));
	}

	return (0);
}

