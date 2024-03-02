#include "shell.h"

/**
 * is_chain_delimiter - Test if the current character
 * in the buffer is a chain delimiter.
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 *
 * Return: 1 if chain delimiter, 0 otherwise.
 */
int is_chain_delimiter(info_t *info, char *buf, size_t *p)
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
		return (0);
	*p = j;
	return (1);
}

/**
 * check_continuation - Checks if we should
 * continue chaining based on the last status.
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * Return: Void.
 */
void check_continuation(info_t *info, char *buf,
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
 * substitute_aliases - Replaces aliases in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int substitute_aliases(info_t *info)
{
	int i;
	list_t *iNode;
	char *p;

	for (i = 0; i < 10; i++)
	{
		iNode = find_node_with_prefix(info->alias, info->argv[0], '=');
		if (!iNode)
			return (0);
		free(info->argv[0]);
		p = _find_character(iNode->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * substitute_variables - Replaces variables in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int substitute_variables(info_t *info)
{
	int i = 0;
	list_t *iNode;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_string_compare(info->argv[i], "$?"))
		{
			substitute_string(&(info->argv[i]),
				_strdup(number_conversion(info->status, 10, 0)));
			continue;
		}
		if (!_string_compare(info->argv[i], "$$"))
		{
			substitute_string(&(info->argv[i]),
				_strdup(number_conversion(getpid(), 10, 0)));
			continue;
		}
		iNode = find_node_with_prefix(info->env, &info->argv[i][1], '=');
		if (iNode)
		{
			substitute_string(&(info->argv[i]),
				_strdup(_find_character(iNode->str, '=') + 1));
			continue;
		}
		substitute_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * substitute_string - Replaces a string.
 * @old: Address of the old string.
 * @new: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int substitute_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

