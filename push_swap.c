#include "push_swap.h"

static int
	dist(t_list *ctx, int value)
{
	int		i;
	t_node	*node;

	i = 1;
	node = ctx[0].frst;
	while (node->next != NULL)
	{
		if (node->value < value && value < node->next->value)
			break ;
		if (value < node->next->value && node->next->value < node->value)
			break ;
		if (value > node->value && node->value > node->next->value)
			break ;
		i += 1;
		node = node->next;
	}
	return (i);
}

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
		i0 = dist(ctx, node->value);
		r_optimize(&i0, ctx[0].size, &i1, ctx[1].size);
		r_min(&j0, i0, &j1, i1);
		i1 += 1;
		node = node->next;
	}
	r_rotate(ctx, j0, j1);
	i_exec(ctx, op_pa);
}

int
	ps_main(t_list *ctx)
{
	int		i;
	t_node	*node;

	while (ctx[0].size > 2)
		i_exec(ctx, op_pb);
	while (ctx[1].size > 0)
		step(ctx);
	node = ctx[0].frst;
	i = 0;
	while (node != NULL)
	{
		i += 1;
		if (node->next == NULL || node->next->value < node->value)
			break ;
		node = node->next;
	}
	r_rotate(ctx, u_absmin(i, i - ctx[0].size), 0);
	return (0);
}
