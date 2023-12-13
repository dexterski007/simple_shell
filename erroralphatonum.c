#include "main.h"

/**
 * erroralphatonum - str to num
 * @s: string
 * Return: 0 or -1
 */
int erroralphatonum(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * errexport - export error
 * @param: param
 * @estr: str
 * Return: 0 or -1
 */
void errexport(param_t *param, char *estr)
{
	putserror(param->fname);
	putserror(": ");
	descriptpr(param->line_count, STDERR_FILENO);
	putserror(": ");
	putserror(param->argv[0]);
	putserror(": ");
	putserror(estr);
}

/**
 * descriptpr - descriptor pointer
 * @input: input
 * @fd: filedescr
 *
 * Return: num of char
 */
int descriptpr(int input, int fd)
{
	int (*_altputchar)(char) = altputchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		_altputchar = putcharerror;
	if (input < 0)
	{
		_abs_ = -input;
		_altputchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			_altputchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	_altputchar('0' + current);
	count++;

	return (count);
}

/**
 * num_conv - num to str
 * @num: num
 * @base: base
 * @flags: flags
 *
 * Return: string
 */
char *num_conv(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & 2) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & 1 ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * comment_rem - rem comment
 * @buffer: buffer
 *
 * Return: 0
 */
void comment_rem(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}
