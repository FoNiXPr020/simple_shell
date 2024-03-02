#include "shell.h"

/**
 * retrieve_history_file - Retrieve the history file.
 * @info: Parameter struct.
 * Return: Allocated string containing the history file.
 */

char *retrieve_history_file(info_t *info)
{
	char *iBuffer, *dir;

	dir = _get_environ(info, "HOME=");
	if (!dir)
		return (NULL);
	iBuffer = malloc(sizeof(char) * (_string_length(dir) +
	_string_length(HIST_FILE) + 2));
	if (!iBuffer)
		return (NULL);
	iBuffer[0] = 0;
	_strcpy(iBuffer, dir);
	_string_concat(iBuffer, "/");
	_string_concat(iBuffer, HIST_FILE);
	return (iBuffer);
}

/**
 * create_or_append_history - Create a file or append to an existing file.
 * @info: The parameter struct.
 * Return: 1 on success, else -1.
 */
int create_or_append_history(info_t *info)
{
	ssize_t fd;
	char *filename = retrieve_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_puts_fd(node->str, fd);
		_put_fd('\n', fd);
	}
	_put_fd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history_from_file - Read history from a file.
 * @info: The parameter struct.
 * Return: Histcount on success, 0 otherwise.
 */
int read_history_from_file(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = retrieve_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			add_entry_to_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		add_entry_to_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		remove_node_at_index(&(info->history), 0);
	renumber_history_list(info);
	return (info->histcount);
}

/**
 * add_entry_to_history_list - Add an entry to a history linked list.
 * @info: Structure containing potential arguments. Used to maintain.
 * @buf: Buffer.
 * @linecount: The history line count, histcount.
 * Return: Always 0.
 */
int add_entry_to_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	append_node(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history_list - Renumber the history linked list after changes.
 * @info: Structure containing potential arguments. Used to maintain.
 * Return: The new histcount.
 */
int renumber_history_list(info_t *info)
{
	list_t *iNode = info->history;
	int i = 0;

	while (iNode)
	{
		iNode->num = i++;
		iNode = iNode->next;
	}
	return (info->histcount = i);
}

