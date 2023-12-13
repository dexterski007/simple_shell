#include "main.h"

/**
 * histget - hist list
 * @param: param
 *
 * Return: 0
 */
int histget(param_t *param)
{
	listpr(param->history);
	return (0);
}

/**
 * remalias - rem alias
 * @param: param
 * @str: str
 *
 * Return: 0 or 1
 */
int remalias(param_t *param, char *str)
{
	char *p, c;
	int ret;

	p = stringsearch(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = noderemind(&(param->alias),
		nodeinddet(param->alias, prefnod(param->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * instalias - inst alias
 * @param: param
 * @str: str
 *
 * Return: 0or 1
 */
int instalias(param_t *param, char *str)
{
	char *p;

	p = stringsearch(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (remalias(param, str));

	remalias(param, str);
	return (nodeplusend(&(param->alias), str, 0) == NULL);
}

/**
 * pralias - print alias
 * @node: node
 *
 * Return: 0 or 1
 */
int pralias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = stringsearch(node->str, '=');
		for (a = node->str; a <= p; a++)
			altputchar(*a);
		altputchar('\'');
		putsring(p + 1);
		putsring("'\n");
		return (0);
	}
	return (1);
}

/**
 * aliasget - alias get
 * @param: param
 *
 * Return: 0
 */
int aliasget(param_t *param)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (param->argc == 1)
	{
		node = param->alias;
		while (node)
		{
			pralias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; param->argv[i]; i++)
	{
		p = stringsearch(param->argv[i], '=');
		if (p)
			instalias(param, param->argv[i]);
		else
			pralias(prefnod(param->alias, param->argv[i], '='));
	}

	return (0);
}
