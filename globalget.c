#include "main.h"

/**
 * globalget - get environ
 * @param: param
 * Return: 0
 */
char **globalget(param_t *param)
{
	if (!param->environ || param->env_changed)
	{
		param->environ = convliststr(param->env);
		param->env_changed = 0;
	}

	return (param->environ);
}

/**
 * envunset2 - env unset
 * @param: param
 * @var: var
 *
 * Return: 1 or 0
 */
int envunset2(param_t *param, char *var)
{
	list_t *node = param->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = prefi(node->str, var);
		if (p && *p == '=')
		{
			param->env_changed = noderemind(&(param->env), i);
			i = 0;
			node = param->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (param->env_changed);
}

/**
 * envset2 - init var
 * @param: param
 * @var: var
 * @value: value
 *
 * Return: 0
 */
int envset2(param_t *param, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);
	buf = malloc(lenstrcalc(var) + lenstrcalc(value) + 2);
	if (!buf)
		return (1);
	copystrs(buf, var);
	concatstr(buf, "=");
	concatstr(buf, value);
	node = param->env;
	while (node)
	{
		p = prefi(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			param->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	nodeplusend(&(param->env), buf, 0);
	free(buf);
	param->env_changed = 1;
	return (0);
}
