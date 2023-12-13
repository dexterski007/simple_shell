#include "main.h"

/**
 * lenlist - len list
 * @h: head
 *
 * Return: size
 */
size_t lenlist(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * convliststr - array to list
 * @head: head
 *
 * Return: array
 */
char **convliststr(list_t *head)
{
	list_t *node = head;
	size_t i = lenlist(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(lenstrcalc(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = copystrs(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * listpr - print list
 * @h: head
 *
 * Return: size
 */
size_t listpr(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		putsring(num_conv(h->num, 10, 0));
		altputchar(':');
		altputchar(' ');
		putsring(h->str ? h->str : "(nil)");
		putsring("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * prefnod - pref node
 * @node: head
 * @prefix: str
 * @c: next char
 *
 * Return: node or null
 */
list_t *prefnod(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = prefi(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * nodeinddet - get index
 * @head: head
 * @node: pointer
 *
 * Return: ind or -1
 */
ssize_t nodeinddet(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
