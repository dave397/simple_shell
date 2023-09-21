#include "main.h"

/**
 * dup_chars - duplicates characters
 * @p_str: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *p_str, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (p_str[i] != ':')
			buf[k++] = p_str[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @global: the global struct
 * @p_str: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(global_t *global, char *p_str, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!p_str)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (_is_cmd(global, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!p_str[i] || p_str[i] == ':')
		{
			path = dup_chars(p_str, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (_is_cmd(global, path))
				return (path);
			if (!p_str[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * _is_cmd - determines if a file is an executable command
 * @global: the global struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int _is_cmd(global_t *global, char *path)
{
	struct stat st;

	(void)global;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
