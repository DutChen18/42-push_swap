#include "push_swap.h"
#include <limits.h>

static int
	dist(t_list *ctx, int value)
{
	int		i;
	t_node	*node;

	i = 0;
	node = ctx[0].frst;
	while (1)
	{
		i += 1;
		if (node->next == NULL)
			break ;
		if ((node->value < value) && (value < node->next->value))
			break ;
		if ((value < node->next->value) && (node->next->value < node->value))
			break ;
		if ((value > node->value) && (node->value > node->next->value))
			break ;
		node = node->next;
	}
	return (i);
}

static int
	m(t_list *ctx, int *i, int d)
{
	t_node	*node;
	int		best;
	int		j;
	int		rot[2];
	int		tmp;

	if (d == 0 || ctx[1].size == 0)
		return (0);
	best = INT_MAX;
	node = ctx[1].frst->next;
	j = 0;
	while (node != NULL)
	{
		rot[0] = dist(ctx, node->value);
		rot[1] = j;
		u_optimize(&rot[0], ctx[0].size, &rot[1], ctx[1].size);
		u_rotate(ctx, rot[0], rot[1]);
		u_exec(ctx, op_pa);
		tmp = u_cost(rot[0], rot[1]) + m(ctx, NULL, d - 1);
		u_exec(ctx, op_pb);
		u_rotate(ctx, -rot[0], -rot[1]);
		if (tmp < best)
		{
			best = tmp;
			if (i != NULL)
				*i = j;
		}
		j += 1;
		node = node->next;
	}
	return (best);
}

static void
	step(t_list *ctx)
{
	t_node	*node;
	int		i;
	int		rot[2];
	int		bst[2];

	node = ctx[1].frst->next;
	bst[0] = dist(ctx, ctx[1].frst->value);
	bst[1] = 0;
	u_optimize(&bst[0], ctx[0].size, &bst[1], ctx[1].size);
	i = 0;
	while (node != NULL)
	{
		i += 1;
		rot[0] = dist(ctx, node->value);
		rot[1] = i;
		u_optimize(&rot[0], ctx[0].size, &rot[1], ctx[1].size);
		u_min(&bst[0], rot[0], &bst[1], rot[1]);
		node = node->next;
	}
	u_rotate(ctx, bst[0], bst[1]);
	u_exec(ctx, op_pa);
}

void
	s_sort(t_list *ctx, int size)
{
	int		i;
	t_node	*node;

	while (ctx[0].size > 2)
		u_exec(ctx, op_pb);
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
	u_rotate(ctx, (i > size / 2) * (i - size) + (i <= size / 2) * i, 0);
}
