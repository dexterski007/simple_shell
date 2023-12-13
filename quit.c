#include "main.h"

/**
 **strincopy2 - str copy
 *@b: dest
 *@a: src
 *@n: num of char
 *Return: str
 */
char *strincopy2(char *b, char *a, int n)
{
	int i, j;
	char *s = b;

	i = 0;
	while (a[i] != '\0' && i < n - 1)
	{
		b[i] = a[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			b[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **stringconcat2 - str concat
 *@b: dest
 *@a: src
 *@n: num of char
 *Return: str
 */
char *stringconcat2(char *b, char *a, int n)
{
	int i, j;
	char *s = b;

	i = 0;
	j = 0;
	while (b[i] != '\0')
		i++;
	while (a[j] != '\0' && j < n)
	{
		b[i] = a[j];
		i++;
		j++;
	}
	if (j < n)
		b[i] = '\0';
	return (s);
}

/**
 **stringsearch - str search
 *@s: str
 *@c: char
 *Return: pointer
 */
char *stringsearch(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * **tokenstring1 - token str
 * @str: str
 * @delim: delim
 * Return: pointer
 */

char **tokenstring1(char *str, char *delim)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!checkdelim(str[i], delim) &&
	(checkdelim(str[i + 1], delim) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (checkdelim(str[i], delim))
			i++;
		k = 0;
		while (!checkdelim(str[i + k], delim) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **tokenstring2 - token str
 * @str: str
 * @delim: delim
 * Return: pointer
 */
char **tokenstring2(char *str, char delim)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
		    (str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;
		k = 0;
		while (str[i + k] != delim && str[i + k] && str[i + k] != delim)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
