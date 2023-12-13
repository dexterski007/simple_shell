#include "main.h"

/**
 * input_buf - inp buff
 * @param: param
 * @buffer: buffer
 * @len: len
 *
 * Return: bytes
 */
ssize_t input_buf(param_t *param, char **buffer, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, signal2);
#if 0
		r = getline(buffer, &len_p, stdin);
#else
		r = linegetter(param, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			param->linecount_flag = 1;
			comment_rem(*buffer);
			histlistcr(param, *buffer, param->histcount++);
			{
				*len = r;
				param->buffer_cmd = buffer;
			}
		}
	}
	return (r);
}

/**
 * getprompt - get prompt
 * @param: param
 *
 * Return: bytes
 */
ssize_t getprompt(param_t *param)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(param->arg), *p;

	altputchar(-1);
	r = input_buf(param, &buffer, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buffer + i;

		chainchk(param, buffer, &j, i, len);
		while (j < len)
		{
			if (detectchain(param, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			param->buffer_cmd_type = 0;
		}

		*buf_p = p;
		return (lenstrcalc(p));
	}

	*buf_p = buffer;
	return (r);
}

/**
 * read_buf - reads buffer
 * @param: param
 * @buffer: buffer
 * @i: index
 *
 * Return: r
 */
ssize_t read_buf(param_t *param, char *buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(param->readfd, buffer, 1024);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * linegetter - get line
 * @param: param
 * @ptr: pointer
 * @length: len
 *
 * Return: str
 */
int linegetter(param_t *param, char **ptr, size_t *length)
{
	static char buffer[1024];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(param, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = stringsearch(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = allocreac(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		stringconcat2(new_p, buffer + i, k - i);
	else
		strincopy2(new_p, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * signal2 - check ctrlc
 * @sig_num: num
 */
void signal2(__attribute__((unused))int sig_num)
{
	putsring("\n");
	putsring("$ ");
	altputchar(-1);
}
