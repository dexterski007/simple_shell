#include "main.h"

/**
 * detectchain - detect chain
 * @param: param
 * @buffer: buffer
 * @p: pointer
 *
 * Return: 1 or 0
 */
int detectchain(param_t *param, char *buffer, size_t *p)
{
	size_t j = *p;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		param->buffer_cmd_type = 1;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		param->buffer_cmd_type = 2;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		param->buffer_cmd_type = 3;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * chainchk - chain check
 * @param: param
 * @buffer: buffer
 * @p: pointer
 * @i: index
 * @len: len
 */
void chainchk(param_t *param, char *buffer, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (param->buffer_cmd_type == 2)
	{
		if (param->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}
	if (param->buffer_cmd_type == 1)
	{
		if (!param->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * aliasvexel - alias replace
 * @param: param
 *
 * Return: 1 or 0
 */
int aliasvexel(param_t *param)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = prefnod(param->alias, param->argv[0], '=');
		if (!node)
			return (0);
		free(param->argv[0]);
		p = stringsearch(node->str, '=');
		if (!p)
			return (0);
		p = doubstr(p + 1);
		if (!p)
			return (0);
		param->argv[0] = p;
	}
	return (1);
}

/**
 * varvexel - replace var
 * @param: param
 *
 * Return: 1 or 0
 */
int varvexel(param_t *param)
{
	int i = 0;
	list_t *node;

	for (i = 0; param->argv[i]; i++)
	{
		if (param->argv[i][0] != '$' || !param->argv[i][1])
			continue;

		if (!comparestr(param->argv[i], "$?"))
		{
			strvexel(&(param->argv[i]),
				doubstr(num_conv(param->status, 10, 0)));
			continue;
		}
		if (!comparestr(param->argv[i], "$$"))
		{
			strvexel(&(param->argv[i]),
				doubstr(num_conv(getpid(), 10, 0)));
			continue;
		}
		node = prefnod(param->env, &param->argv[i][1], '=');
		if (node)
		{
			strvexel(&(param->argv[i]),
				doubstr(stringsearch(node->str, '=') + 1));
			continue;
		}
		strvexel(&param->argv[i], doubstr(""));

	}
	return (0);
}

/**
 * strvexel - replace str
 * @b: pointer
 * @a: str
 *
 * Return: 1 or 0
 */
int strvexel(char **b, char *a)
{
	free(*b);
	*b = a;
	return (1);
}
