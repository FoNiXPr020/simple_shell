#include "shell.h"

/**
 * custom_is_chain - Tests if the current character
 * in the buffer is a chain delimiter.
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 * Return: 1 if a chain delimiter, 0 otherwise.
 */
int custom_is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}
	*p = j;
	return (1);
}

/**
 * custom_check_chain - Checks whether to continue
 * chaining based on the last status.
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 * Return: Void.
 */
void custom_check_chain(info_t *info, char *buf,
				size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * custom_replace_alias - Replaces aliases in the tokenized string.
 * @info: The parameter struct.
 * Return: 1 if replaced, 0 otherwise.
 */
int custom_replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = custom_node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
		{
			return (0);
		}

		free(info->argv[0]);
		p = custom_strchr(node->str, '=');
		if (!p)
		{
			return (0);
		}

		p = custom_strdup(p + 1);
		if (!p)
		{
			return (0);
		}

		info->argv[0] = p;
	}
	return (1);
}

/**
 * custom_replace_vars - Replaces variables in the tokenized string.
 * @info: The parameter struct.
 * Return: 1 if replaced, 0 otherwise.
 */
int custom_replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
		{
			continue;
		}
		if (custom_strcmp(info->argv[i], "$?") == 0)
		{
			custom_replace_string(&(info->argv[i]),
			custom_strdup(custom_convert_number(info->status, 10, 0)));
			continue;
		}
		if (custom_strcmp(info->argv[i], "$$") == 0)
		{
			custom_replace_string(&(info->argv[i]),
			custom_strdup(custom_convert_number(getpid(), 10, 0)));
			continue;
		}

		node = custom_node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			custom_replace_string(&(info->argv[i]),
			custom_strdup(custom_strchr(node->str, '=') + 1));
			continue;
		}

		custom_replace_string(&info->argv[i], custom_strdup(""));
	}
	return (0);
}

/**
 * custom_replace_string - Replaces a string.
 * @old: Address of the old string.
 * @new: New string.
 * Return: 1 if replaced, 0 otherwise.
 */
int custom_replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

