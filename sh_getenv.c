#include "shell.h"

/**
 * copy_environment - Return a copy of the string array "environ".
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always returns 0
 */
char **copy_environment(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = convert_list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _remove_env_var - Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The environment variable property to remove
 * Return: Returns 1 on deletion, 0 otherwise
 */
int _remove_env_var(info_t *info, char *var)
{
	list_t *iNode = info->env;
	size_t i = 0;
	char *p;

	if (!iNode || !var)
		return (0);

	while (iNode)
	{
		p = check_prefix(iNode->str, var);
		if (p && *p == '=')
		{
			info->env_changed = remove_node_at_index(&(info->env), i);
			i = 0;
			iNode = info->env;
			continue;
		}
		iNode = iNode->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _set_env_var - Initialize a new
 * environment variable or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The environment variable property
 * @value: The environment variable value
 * Return: Always returns 0
 */
int _set_env_var(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_string_length(var) + _string_length(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_string_concat(buf, "=");
	_string_concat(buf, value);
	node = info->env;
	while (node)
	{
		p = check_prefix(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	append_node(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

