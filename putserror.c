#include "main.h"

/**
 *putserror - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void putserror(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		putcharerror(str[i]);
		i++;
	}
}

/**
 * putcharerror - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int putcharerror(char c)
{
	static int i;
	static char buf[1024];

	if (c == -1 || i >= 1024)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != -1)
		buf[i++] = c;
	return (1);
}

/**
 * filedescput - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int filedescput(char c, int fd)
{
	static int i;
	static char buf[1024];

	if (c == -1 || i >= 1024)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != -1)
		buf[i++] = c;
	return (1);
}

/**
 *filedescputstr - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int filedescputstr(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += filedescput(*str++, fd);
	}
	return (i);
}
