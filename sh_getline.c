#include "shell.h"

/**
 * buffer_input - Buffer chained commands.
 * @info: Parameter struct.
 * @buf: Address of buffer.
 * @len: Address of length variable.
 * Return: Number of bytes read.
 */
ssize_t buffer_input(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handle_SIGINT);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _retrieve_line(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			eliminate_comments(*buf);
			add_entry_to_history_list(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input_newline - Get a line without the newline character.
 * @info: Parameter struct.
 * Return: Number of bytes read.
 */
ssize_t get_input_newline(info_t *info)
{
	static char *iBuffer;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUFFER_FLUSH);
	r = buffer_input(info, &iBuffer, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = iBuffer + i;

		check_continuation(info, iBuffer, &j, i, len);
		while (j < len)
		{
			if (is_chain_delimiter(info, iBuffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_string_length(p));
	}

	*buf_p = iBuffer;
	return (r);
}

/**
 * read_buffer - Read a buffer.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @i: Size.
 * Return: r
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _retrieve_line - Retrieve the next line of input from STDIN.
 * @info: Parameter struct.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 * Return: s
 */
int _retrieve_line(info_t *info, char **ptr, size_t *length)
{
	static char iBuffer[READ_BUFFER_SIZE];
	static size_t i, iLen;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == iLen)
		i = iLen = 0;

	r = read_buffer(info, iBuffer, &iLen);
	if (r == -1 || (r == 0 && iLen == 0))
		return (-1);

	c = _find_character(iBuffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - iBuffer) : iLen;
	new_p = _reallocate(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_cat_strings_n(new_p, iBuffer + i, k - i);
	else
		_copy_string_n(new_p, iBuffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * handle_SIGINT - Block SIGINT (Ctrl-C) signal.
 * @sig_num: The signal number.
 * Return: Void.
 */
void handle_SIGINT(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}

