#include "main.h"

/**
 * copystrs - str copy
 * @b: dest
 * @a: src
 *
 * Return: pointer
 */
char *copystrs(char *b, char *a)
{
	int i = 0;

	if (b == a || a == 0)
		return (b);
	while (a[i])
	{
		b[i] = a[i];
		i++;
	}
	b[i] = 0;
	return (b);
}

/**
 * doubstr - double str
 * @str: str
 *
 * Return: pointer
 */
char *doubstr(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *putsring - put string
 *@str: str
 */
void putsring(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		altputchar(str[i]);
		i++;
	}
}

/**
 * altputchar - putchar
 * @c: char
 *
 * Return: 1
 */
int altputchar(char c)
{
	static int i;
	static char buf[1024];

	if (c == -1 || i >= 1024)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != -1)
		buf[i++] = c;
	return (1);
}
