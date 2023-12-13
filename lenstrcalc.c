#include "main.h"

/**
 * lenstrcalc - calc len str
 * @s: str
 *
 * Return: str len
 */
int lenstrcalc(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * comparestr - compare str
 * @s1: str 1
 * @s2: str 2
 *
 * Return: -1 or 1
 */
int comparestr(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * prefi - check prefix
 * @string: string
 * @substr: substring
 *
 * Return: pointer or null
 */
char *prefi(const char *string, const char *substr)
{
	while (*substr)
		if (*substr++ != *string++)
			return (NULL);
	return ((char *)string);
}

/**
 * concatstr - str concat
 * @b: dest
 * @a: src
 *
 * Return: pointer
 */
char *concatstr(char *b, char *a)
{
	char *ret = b;

	while (*b)
		b++;
	while (*a)
		*b++ = *a++;
	*b = *a;
	return (ret);
}
