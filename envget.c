#include "main.h"

/**
 * envdetect - prints the current environment
 * @param: param
 * Return: 0
 */
int envdetect(param_t *param)
{
	listprstr(param->env);
	return (0);
}

/**
 * envget - gets the value of an environ variable
 * @param: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *envget(param_t *param, const char *name)
{
	list_t *node = param->env;
	char *p;

	while (node)
	{
		p = prefi(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * envset - Initialize a new environment variable,
 *             or modify an existing one
 * @param: param
 *  Return: 0
 */
int envset(param_t *param)
{
	if (param->argc != 3)
	{
		putserror("Incorrect number of arguements\n");
		return (1);
	}
	if (envset2(param, param->argv[1], param->argv[2]))
		return (0);
	return (1);
}

/**
 * envunset - Remove an environment variable
 * @param: param
 *  Return: 0
 */
int envunset(param_t *param)
{
	int i;

	if (param->argc == 1)
	{
		putserror("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= param->argc; i++)
		envunset2(param, param->argv[i]);

	return (0);
}

/**
 * listenvfill - populates env linked list
 * @param: param
 * Return: 0
 */
int listenvfill(param_t *param)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		nodeplusend(&node, environ[i], 0);
	param->env = node;
	return (0);
}
