/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 10:32:02 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/17 12:42:02 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static int
	m_atoi(char *str, int *v)
{
	int	s;

	if (!*str)
		return (-1);
	s = 1 - (*str == '-') * 2;
	str += *str == '-';
	*v = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (*v > INT_MAX / 10 || (s > 0 && *v * 10 > INT_MAX - (*str - '0')))
			return (-1);
		if (*v < INT_MIN / 10 || (s < 0 && *v * 10 < INT_MIN + (*str - '0')))
			return (-1);
		*v = *v * 10 + (*str - '0') * s;
		str += 1;
	}
	if (*str)
		return (-1);
	return (0);
}

static int
	m_init(char **argv, t_list *list, int (fn)(t_list *))
{
	t_node	node;
	t_node	*ptr;

	if (*argv == NULL)
		return (fn(list));
	if (m_atoi(*argv, &node.value) < 0)
		return (-1);
	ptr = list->frst;
	while (ptr != NULL)
	{
		if (ptr->value == node.value)
			return (-1);
		ptr = ptr->next;
	}
	l_add_last(list, &node);
	return (m_init(argv + 1, list, fn));
}

static int
	m_run(t_list *list)
{
	t_list	ctx[2];

	if (list->size < 1)
		return (0);
	ctx[0] = *list;
	ctx[1].frst = NULL;
	ctx[1].last = NULL;
	ctx[1].size = 0;
	return (ps_main(ctx));
}

int
	main(int argc, char **argv)
{
	t_list	list;

	(void) argc;
	list.frst = NULL;
	list.last = NULL;
	list.size = 0;
	if (m_init(argv + 1, &list, m_run) < 0)
		write(2, "Error\n", 6);
	return (EXIT_SUCCESS);
}
