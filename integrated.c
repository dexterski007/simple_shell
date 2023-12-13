#include "main.h"

/**
 * quits - quit
 * @param: param
 *
 * Return: exit status
 */
int quits(param_t *param)
{
	int exitcheck;

	if (param->argv[1])
	{
		exitcheck = erroralphatonum(param->argv[1]);
		if (exitcheck == -1)
		{
			param->status = 2;
			errexport(param, "error number: ");
			putserror(param->argv[1]);
			putcharerror('\n');
			return (1);
		}
		param->err_num = erroralphatonum(param->argv[1]);
		return (-2);
	}
	param->err_num = -1;
	return (-2);
}

/**
 * chngedir - chnage dir
 * @param: param
 *
 * Return: 0
 */
int chngedir(param_t *param)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		putsring("cant change dir\n");
	if (!param->argv[1])
	{
		dir = envget(param, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = envget(param, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (comparestr(param->argv[1], "-") == 0)
	{
		if (!envget(param, "OLDPWD="))
		{
			putsring(s);
			altputchar('\n');
			return (1);
		}
		putsring(envget(param, "OLDPWD=")), altputchar('\n');
		chdir_ret =
			chdir((dir = envget(param, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(param->argv[1]);
	if (chdir_ret == -1)
	{
		errexport(param, "can't cd to ");
		putserror(param->argv[1]), putcharerror('\n');
	}
	else
	{
		envset2(param, "OLDPWD", envget(param, "PWD="));
		envset2(param, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * helpget - help
 * @param: param
 *
 * Return: 0
 */
int helpget(param_t *param)
{
	char **arg_array;

	arg_array = param->argv;
	putsring("help me i am bruning out");
	if (0)
		putsring(*arg_array);
	return (0);
}
