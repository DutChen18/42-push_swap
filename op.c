#include "push_swap.h"

void
	o_swap(t_list *ctx, int op)
{
	t_node	*n1;
	t_node	*n2;

	if (op == 2)
	{
		o_swap(ctx, 0);
		o_swap(ctx, 1);
	}
	else
	{
		n1 = l_pop_frst(&ctx[op]);
		n2 = l_pop_frst(&ctx[op]);
		l_add_frst(&ctx[op], n1);
		l_add_frst(&ctx[op], n2);
	}
}

void
	o_push(t_list *ctx, int op)
{
	t_node	*n1;

	n1 = l_pop_frst(&ctx[1 - op]);
	l_add_frst(&ctx[op], n1);
}

void
	o_shup(t_list *ctx, int op)
{
	t_node	*n1;

	if (op == 2)
	{
		o_shup(ctx, 0);
		o_shup(ctx, 1);
	}
	else
	{
		n1 = l_pop_frst(&ctx[op]);
		l_add_last(&ctx[op], n1);
	}
}

void
	o_shdo(t_list *ctx, int op)
{
	t_node	*n1;

	if (op == 2)
	{
		o_shdo(ctx, 0);
		o_shdo(ctx, 1);
	}
	else
	{
		n1 = l_pop_last(&ctx[op]);
		l_add_frst(&ctx[op], n1);
	}
}

void
	o_exec(t_list *ctx, int op)
{
	if (op >> 2 == 0)
		o_swap(ctx, op & 3);
	if (op >> 2 == 1)
		o_push(ctx, op & 3);
	if (op >> 2 == 2)
		o_shup(ctx, op & 3);
	if (op >> 2 == 3)
		o_shdo(ctx, op & 3);
}
