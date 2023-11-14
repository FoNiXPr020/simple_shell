#include "shell.h"

/**
 * custom_input_buf - Buffers chained commands.
 * @info: Parameter struct.
 * @buf: Address of the buffer.
 * @len: Address of the len variable.
 * Return: Bytes read.
 */
ssize_t custom_input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* If nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, custom_sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = custom_getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* Remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			custom_remove_comments(*buf);
			custom_build_history_list(info, *buf, info->histcount++);
			/* If (_strchr(*buf, ';')) Is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * custom_get_input - Gets a line minus the newline.
 * @info: Parameter struct.
 * Return: Bytes read.
 */
ssize_t custom_get_input(info_t *info)
{
	static char *buf; /* The ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	custom_putchar(BUF_FLUSH);
	r = custom_input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* We have commands left in the chain buffer */
	{
		j = i; /* Initialize a new iterator to the current buf position */
		p = buf + i; /* Get a pointer for return */

		custom_check_chain(info, buf, &j, i, len);
		while (j < len) /* Iterate to semicolon or end */
		{
			if (custom_is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* Increment past nulled ';'' */
		if (i >= len) /* Reached the end of the buffer? */
		{
			i = len = 0; /* Reset position and length */
			info->cmd_buf_type = CMD_NORMAL;
		}

		*buf_p = p; /* Pass back a pointer to the current command position */
		return (custom_strlen(p)); /* Return the length of the current command */
	}

	*buf_p = buf; /* Else, not a chain, info_ts back the buffer from _getline() */
	return (r); /* Return the length of the buffer from _getline() */
}

/**
 * custom_read_buf - Reads a buffer.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @i: Size.
 * Return: r.
 */
ssize_t custom_read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, CUSTOM_READ_BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * custom_getline - Gets the next line of input from STDIN.
 * @info: Parameter struct.
 * @ptr: Address of a pointer to a buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 * Return: s.
 */
int custom_getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[CUSTOM_READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = custom_read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = custom_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = custom_realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		custom_strncat(new_p, buf + i, k - i);
	else
		custom_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * custom_sigintHandler - Blocks ctrl-C.
 * @sig_num: The signal number.
 * Return: void.
 */
void custom_sigintHandler(__attribute__((unused))int sig_num)
{
	custom_puts("\n");
	custom_puts("$ ");
	custom_putchar(BUF_FLUSH);
}

