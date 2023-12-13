#include "main.h"

/**
 * hoshell - holberton shell
 * @param: param
 * @av: av
 *
 * Return: 0 or 1
 */
int hoshell(param_t *param, char **av)
{
	ssize_t r = 0;
	int integrated_ret = 0;

	while (r != -1 && integrated_ret != -2)
	{
		reminf(param);
		if (checkinter(param))
			putsring("$ ");
		putcharerror(-1);
		r = getprompt(param);
		if (r != -1)
		{
			putinf(param, av);
			integrated_ret = find_integrated(param);
			if (integrated_ret == -1)
				cmdseek(param);
		}
		else if (checkinter(param))
			altputchar('\n');
		cleaninf(param, 0);
	}
	histput(param);
	cleaninf(param, 1);
	if (!checkinter(param) && param->status)
		exit(param->status);
	if (integrated_ret == -2)
	{
		if (param->err_num == -1)
			exit(param->status);
		exit(param->err_num);
	}
	return (integrated_ret);
}

/**
 * find_integrated - find cmd
 * @param: param
 *
 * Return: -1 0 1 or 2
 */
int find_integrated(param_t *param)
{
	int i, built_in_ret = -1;
	integrated_table integratedtbl[] = {
		{"exit", quits},
		{"env", envdetect},
		{"help", helpget},
		{"history", histget},
		{"setenv", envset},
		{"unsetenv", envunset},
		{"cd", chngedir},
		{"alias", aliasget},
		{NULL, NULL}
	};

	for (i = 0; integratedtbl[i].type; i++)
		if (comparestr(param->argv[0], integratedtbl[i].type) == 0)
		{
			param->line_count++;
			built_in_ret = integratedtbl[i].func(param);
			break;
		}
	return (built_in_ret);
}

/**
 * cmdseek - search cmd
 * @param: param
 */
void cmdseek(param_t *param)
{
	char *path = NULL;
	int i, k;

	param->path = param->argv[0];
	if (param->linecount_flag == 1)
	{
		param->line_count++;
		param->linecount_flag = 0;
	}
	for (i = 0, k = 0; param->arg[i]; i++)
		if (!checkdelim(param->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = pathseek(param, envget(param, "PATH="), param->argv[0]);
	if (path)
	{
		param->path = path;
		cmddup(param);
	}
	else
	{
		if ((checkinter(param) || envget(param, "PATH=")
			|| param->argv[0][0] == '/') && cmdcheck(param, param->argv[0]))
			cmddup(param);
		else if (*(param->arg) != '\n')
		{
			param->status = 127;
			errexport(param, "404\n");
		}
	}
}

/**
 * cmddup - dupli cmd
 * @param: param
 */
void cmddup(param_t *param)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error: cannot duplicate");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(param->path, param->argv, globalget(param)) == -1)
		{
			cleaninf(param, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(param->status));
		if (WIFEXITED(param->status))
		{
			param->status = WEXITSTATUS(param->status);
			if (param->status == 126)
				errexport(param, "Error : Permission denied\n");
		}
	}
}
