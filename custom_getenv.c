#include "shell.h"

/**
 * custom_get_environ - Returns a string array copy of the environment.
 * @info: Structure containing potential arguments. Used to maintain a
 *        constant function prototype.
 * Return: The environment variables as a string array.
 */
char **custom_get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = custom_list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * custom_unsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain a
 * constant function prototype.
 * @var: The string environment variable property.
 * Return: 1 on delete, 0 otherwise.
 */
int custom_unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
	{
		return (0);
	}

	while (node)
	{
		p = custom_starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = custom_delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}

	return (info->env_changed);
}

/**
 * custom_setenv - Initialize a new environment
 * variable, or modify an existing one.
 * @info: Structure containing potential arguments.
 * Used to maintain a constant
 * function prototype.
 * @var: The string environment variable property.
 * @value: The string environment variable value.
 * Return: Always 0.
 */
int custom_setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
	{
		return (0);
	}

	buf = malloc(custom_strlen(var) + custom_strlen(value) + 2);
	if (!buf)
	{
		return (1);
	}

	custom_strcpy(buf, var);
	custom_strcat(buf, "=");
	custom_strcat(buf, value);
	node = info->env;

	while (node)
	{
		p = custom_starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	custom_add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;

	return (0);
}

