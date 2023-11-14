#include "shell.h"

/**
 * custom_get_history_file - Gets the history file.
 * @info: Parameter struct.
 * Return: Allocated string containing history file.
 */
char *custom_get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = custom_getenv(info, "HOME=");
	if (!dir)
		return (NULL);

	buf = malloc(custom_strlen(dir) + custom_strlen(HISTORY_FILE) + 2);
	if (!buf)
		return (NULL);

	buf[0] = 0;
	custom_strcpy(buf, dir);
	custom_strcat(buf, "/");
	custom_strcat(buf, HISTORY_FILE);

	return (buf);
}

/**
 * custom_write_history - Creates a file or appends to an existing file.
 * @info: The parameter struct.
 * Return: 1 on success, else -1.
 */
int custom_write_history(info_t *info)
{
	ssize_t fd;
	char *filename = custom_get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		custom_putsfd(node->str, fd);
		custom_putfd('\n', fd);
	}

	custom_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}

/**
 * read_history - Reads history from a file.
 * @info: The parameter struct.
 * Return: Histcount on success, 0 otherwise.
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = custom_get_history_file(info);

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
			custom_build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		custom_build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HISTORY_MAX)
		custom_delete_node_at_index(&(info->history), 0);
	custom_renumber_history(info);
	return (info->histcount);
}

/**
 * custom_build_history_list - Adds an entry to a history linked list.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @linecount: The history line count, histcount.
 * Return: Always 0.
 */
int custom_build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	custom_add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;

	return (0);
}

/**
 * custom_renumber_history - Renumbers the history linked list after changes.
 * @info: Parameter struct.
 * Return: The new histcount.
 */
int custom_renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcount = i);
}

