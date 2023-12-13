#include "main.h"

/**
 * cmdcheck - check cmd
 * @param: param
 * @path: path
 *
 * Return: 1 or 0
 */
int cmdcheck(param_t *param, char *path)
{
	struct stat st;

	(void)param;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * chardup - dup char
 * @pathstr: path str
 * @start: start ind
 * @end: end ind
 *
 * Return: ptr
 */
char *chardup(char *pathstr, int start, int end)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < end; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * pathseek - searhc path
 * @param: param
 * @pathstr: path str
 * @cmd: cmd
 *
 * Return: path or noull
 */
char *pathseek(param_t *param, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((lenstrcalc(cmd) > 2) && prefi(cmd, "./"))
	{
		if (cmdcheck(param, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = chardup(pathstr, curr_pos, i);
			if (!*path)
				concatstr(path, cmd);
			else
			{
				concatstr(path, "/");
				concatstr(path, cmd);
			}
			if (cmdcheck(param, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
