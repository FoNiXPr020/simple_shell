#include "shell.h"

/**
 * check_command - Determine if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int check_command(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_characters - Duplicate characters.
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to the new buffer.
 */
char *duplicate_characters(char *pathstr, int start, int stop)
{
	static char iBuffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			iBuffer[k++] = pathstr[i];
	iBuffer[k] = 0;
	return (iBuffer);
}

/**
 * search_in_path - Find this command in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Return: Full path of command if found or NULL.
 */
char *search_in_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, current_pos = 0;
	char *iPath;

	if (!pathstr)
		return (NULL);
	if ((_string_length(cmd) > 2) && check_prefix(cmd, "./"))
	{
		if (check_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			iPath = duplicate_characters(pathstr, current_pos, i);
			if (!*iPath)
				_string_concat(iPath, cmd);
			else
			{
				_string_concat(iPath, "/");
				_string_concat(iPath, cmd);
			}
			if (check_command(info, iPath))
				return (iPath);
			if (!pathstr[i])
				break;
			current_pos = i;
		}
		i++;
	}
	return (NULL);
}
