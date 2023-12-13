#include "main.h"

/**
 * checkinter - checkinter
 * @param: param
 *
 * Return: 1 or 0
 */
int checkinter(param_t *param)
{
	return (isatty(STDIN_FILENO) && param->readfd <= 2);
}

/**
 * checkdelim - check delim
 * @c: char
 * @delim: delim
 * Return: 1 or 0
 */
int checkdelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *checkalph - check alfa
 *@c: char
 *Return: 1 or 0
 */

int checkalph(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *alphatonum - str to int
 *@s: str
 *Return: 0 or num
 */

int alphatonum(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

