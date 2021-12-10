#include "push_swap.h"

void
	c_swap(t_ctx *ctx, int op)
{
	t_node	*n1;
	t_node	*n2;

	if (op == 2)
	{
		c_swap(ctx, 0);
		c_swap(ctx, 1);
	}
	else
	{
		n1 = l_pop_frst(&ctx->stacks[op]);
		n2 = l_pop_frst(&ctx->stacks[op]);
		l_add_frst(&ctx->stacks[op], n1);
		l_add_frst(&ctx->stacks[op], n2);
	}
}

void
	c_push(t_ctx *ctx, int op)
{
	t_node	*n1;

	n1 = l_pop_frst(&ctx->stacks[1 - op]);
	l_add_frst(&ctx->stacks[op], n1);
}

void
	c_shup(t_ctx *ctx, int op)
{
	t_node	*n1;

	if (op == 2)
	{
		c_shup(ctx, 0);
		c_shup(ctx, 1);
	}
	else
	{
		n1 = l_pop_frst(&ctx->stacks[op]);
		l_add_last(&ctx->stacks[op], n1);
	}
}

void
	c_shdo(t_ctx *ctx, int op)
{
	t_node	*n1;

	if (op == 2)
	{
		c_shdo(ctx, 0);
		c_shdo(ctx, 1);
	}
	else
	{
		n1 = l_pop_last(&ctx->stacks[op]);
		l_add_frst(&ctx->stacks[op], n1);
	}
}

void
	c_exec(t_ctx *ctx, int op)
{
	if (op >> 2 == 0)
		c_swap(ctx, op & 3);
	if (op >> 2 == 1)
		c_push(ctx, op & 3);
	if (op >> 2 == 2)
		c_shup(ctx, op & 3);
	if (op >> 2 == 3)
		c_shdo(ctx, op & 3);
}
