#include "main.h"

/**
 * histfileget - get history
 * @param: param
 *
 * Return: string
 */

char *histfileget(param_t *param)
{
	char *buf, *dir;

	dir = envget(param, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (lenstrcalc(dir) + lenstrcalc(".history") + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	copystrs(buf, dir);
	concatstr(buf, "/");
	concatstr(buf, ".history");
	return (buf);
}

/**
 * histput - add histr
 * @param: param
 *
 * Return: 1 or -1
 */
int histput(param_t *param)
{
	ssize_t filed;
	char *filename = histfileget(param);
	list_t *node = NULL;

	if (!filename)
		return (-1);
	filed = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (filed == -1)
		return (-1);
	for (node = param->history; node; node = node->next)
	{
		filedescputstr(node->str, filed);
		filedescput('\n', filed);
	}
	filedescput(-1, filed);
	close(filed);
	return (1);
}

/**
 * histgetfile - get hist file
 * @param: param
 *
 * Return: histcount or 0
 */
int histgetfile(param_t *param)
{
	int i, last = 0, linecount = 0;
	ssize_t filed, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = histfileget(param);

	if (!filename)
		return (0);

	filed = open(filename, O_RDONLY);
	free(filename);
	if (filed == -1)
		return (0);
	if (!fstat(filed, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(filed, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(filed);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			histlistcr(param, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		histlistcr(param, buf + last, linecount++);
	free(buf);
	param->histcount = linecount;
	while (param->histcount-- >= 4096)
		noderemind(&(param->history), 0);
	histenum(param);
	return (param->histcount);
}

/**
 * histlistcr - add hist to list
 * @param: param
 * @buf: buffer
 * @linecount: linecnt
 *
 * Return: 0
 */
int histlistcr(param_t *param, char *buf, int linecount)
{
	list_t *node = NULL;

	if (param->history)
		node = param->history;
	nodeplusend(&node, buf, linecount);

	if (!param->history)
		param->history = node;
	return (0);
}

/**
 * histenum - recount
 * @param: param
 *
 * Return: count
 */
int histenum(param_t *param)
{
	list_t *node = param->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (param->histcount = i);
}
