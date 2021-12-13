#include "push_swap.h"
#include <limits.h>

static int
	dist(t_list *ctx, int value)
{
	int		i;
	t_node	*node;

	i = 1;
	node = ctx[0].frst;
	while (node->next != NULL)
	{
		if ((node->value < value) && (value < node->next->value))
			break ;
		if ((value < node->next->value) && (node->next->value < node->value))
			break ;
		if ((value > node->value) && (node->value > node->next->value))
			break ;
		i += 1;
		node = node->next;
	}
	return (i);
}

static void
	step(t_list *ctx)
{
	t_node	*node;
	int		i;
	int		rot[2];
	int		bst[2];

	node = ctx[1].frst;
	i = 0;
	while (node != NULL)
	{
		rot[0] = dist(ctx, node->value);
		rot[1] = i;
		u_optimize(&rot[0], ctx[0].size, &rot[1], ctx[1].size);
		if (i == 0 || u_cost(rot[0], rot[1]) < u_cost(bst[0], bst[1]))
		{
			bst[0] = rot[0];
			bst[1] = rot[1];
		}
		node = node->next;
		i += 1;
	}
	dump(&ctx[0]);
	dump(&ctx[1]);
	u_rotate(ctx, 1, bst[0], bst[1]);
	u_exec(ctx, 1, op_pa);
}

void
	s_sort(t_list *ctx, int size)
{
	int		i;
	t_node	*node;

	while (ctx[0].size > 2)
		u_exec(ctx, 1, op_pb);
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
	u_rotate(ctx, 1, (i > size / 2) * (i - size) + (i <= size / 2) * i, 0);
}
