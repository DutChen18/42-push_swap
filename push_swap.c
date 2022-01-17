/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 10:32:07 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/17 12:47:47 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void
	step(t_list *ctx)
{
	int		i0;
	int		i1;
	int		j0;
	int		j1;
	t_node	*node;

	j0 = ctx[0].size;
	j1 = ctx[1].size;
	i1 = 0;
	node = ctx[1].frst;
	while (node != NULL)
	{
		if (u_min(i1, ctx[1].size - i1) < r_cost(j0, j1))
		{
			i0 = a_position(&ctx[0], node->value);
			r_optimize(&i0, ctx[0].size, &i1, ctx[1].size);
			r_min(&j0, i0, &j1, i1);
		}
		i1 = (i1 + ctx[1].size + 1) % ctx[1].size;
		node = node->next;
	}
	r_rotate(ctx, j0, j1);
	i_exec(ctx, op_pa);
}

static void
	sort_part(t_list *ctx, int max)
{
	int	i;
	int	value;

	i = ctx[0].size;
	while (i > 0)
	{
		value = ctx[0].frst->value;
		if (value <= max)
			i_exec(ctx, op_pb);
		else
			i_exec(ctx, op_ra);
		i -= 1;
	}
}

static void
	sort_fast(t_list *ctx)
{
	t_node	*a;
	t_node	*b;
	t_node	*c;

	a = ctx[0].frst;
	b = a->next;
	c = b->next;
	if (a->value < b->value && b->value < c->value)
		return ;
	if (b->value < c->value && c->value < a->value)
		return ;
	if (c->value < a->value && a->value < b->value)
		return ;
	i_exec(ctx, op_sa);
}

int
	ps_main(t_list *ctx)
{
	int		i;

	if (a_sorted(&ctx[0]))
		return (0);
	while (ctx[0].size > CHUNK_SIZE + 3)
	{
		i = a_select(&ctx[0], u_min(CHUNK_SIZE - 1, ctx[0].size - 4));
		sort_part(ctx, i);
	}
	while (ctx[0].size > 3)
		i_exec(ctx, op_pb);
	if (ctx[0].size == 3)
		sort_fast(ctx);
	while (ctx[1].size > 0)
		step(ctx);
	i = a_min_index(&ctx[0]);
	r_rotate(ctx, u_absmin(i, i - ctx[0].size), 0);
	return (0);
}
