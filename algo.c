/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   algo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 10:31:48 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/17 10:31:52 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

static int
	between(int a, int b, int c)
{
	if (a < b && b < c)
		return (1);
	if (a < b && a > c)
		return (1);
	if (b < c && a > c)
		return (1);
	return (0);
}

int
	a_position(t_list *list, int value)
{
	int		i;
	t_node	*node;

	i = 1;
	node = list->frst;
	while (node->next != NULL)
	{
		if (between(node->value, value, node->next->value))
			break ;
		i += 1;
		node = node->next;
	}
	return (i);
}

int
	a_min_index(t_list *list)
{
	int		i;
	int		j;
	int		value;
	t_node	*node;

	i = 0;
	node = list->frst;
	value = INT_MAX;
	while (node != NULL)
	{
		if (node->value <= value)
		{
			value = node->value;
			j = i;
		}
		i += 1;
		node = node->next;
	}
	return (j);
}

int
	a_select(t_list *list, int n)
{
	int		i;
	t_node	*a;
	t_node	*b;

	a = list->frst;
	while (1)
	{
		i = 0;
		b = list->frst;
		while (b != NULL)
		{
			if (b->value < a->value)
				i += 1;
			b = b->next;
		}
		if (i == n)
			return (a->value);
		a = a->next;
	}
}
