#include "main.h"

/**
 * main - main
 * @ac: argc
 * @av: argv
 *
 * Return: 0 or 1
 */
int main(int ac, char **av)
{
	param_t param[] = { param_INIT };
	int fd = 5;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				putserror(av[0]);
				putserror(": 0: Can't open ");
				putserror(av[1]);
				putcharerror('\n');
				putcharerror(-1);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		param->readfd = fd;
	}
	listenvfill(param);
	histgetfile(param);
	hoshell(param, av);
	return (EXIT_SUCCESS);
}

/**
 **setmemory - set mem
 *@s: pptr to mem
 *@b: bye
 *@n: size
 *Return: ptr to mem
 */
char *setmemory(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * freemem2 - free mem
 * @ptr: pointer
 *
 * Return: 1 or 0
 */
int freemem2(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * freemem1 - free mem 1
 * @pp: str to str
 */
void freemem1(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * allocreac - alloc block
 * @ptr: pttr to block
 * @old: old
 * @new: new
 *
 * Return: ptttr
 */
void *allocreac(void *ptr, unsigned int old, unsigned int new)
{
	char *p;

	if (!ptr)
		return (malloc(new));
	if (!new)
		return (free(ptr), NULL);
	if (new == old)
		return (ptr);

	p = malloc(new);
	if (!p)
		return (NULL);

	old = old < new ? old : new;
	while (old--)
		p[old] = ((char *)ptr)[old];
	free(ptr);
	return (p);
}

