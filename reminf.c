#include "main.h"

/**
 * reminf - reminf
 * @param: param
 */
void reminf(param_t *param)
{
	param->arg = NULL;
	param->argv = NULL;
	param->path = NULL;
	param->argc = 0;
}

/**
 * putinf - putinf
 * @param: param
 * @av: arg
 */
void putinf(param_t *param, char **av)
{
	int i = 0;

	param->fname = av[0];
	if (param->arg)
	{
		param->argv = tokenstring1(param->arg, " \t");
		if (!param->argv)
		{

			param->argv = malloc(sizeof(char *) * 2);
			if (param->argv)
			{
				param->argv[0] = doubstr(param->arg);
				param->argv[1] = NULL;
			}
		}
		for (i = 0; param->argv && param->argv[i]; i++)
			;
		param->argc = i;

		aliasvexel(param);
		varvexel(param);
	}
}

/**
 * cleaninf - free param
 * @param: param
 * @all: all
 */
void cleaninf(param_t *param, int all)
{
	freemem1(param->argv);
	param->argv = NULL;
	param->path = NULL;
	if (all)
	{
		if (!param->buffer_cmd)
			free(param->arg);
		if (param->env)
			listfree(&(param->env));
		if (param->history)
			listfree(&(param->history));
		if (param->alias)
			listfree(&(param->alias));
		freemem1(param->environ);
			param->environ = NULL;
		freemem2((void **)param->buffer_cmd);
		if (param->readfd > 2)
			close(param->readfd);
		altputchar(-1);
	}
}
