#include "push_swap.h"
#include <unistd.h>

static const char	*g_ops[] = {
	"sa",
	"sb",
	"ss",
	NULL,
	"pa",
	"pb",
	NULL,
	NULL,
	"ra",
	"rb",
	"rr",
	NULL,
	"rra",
	"rrb",
	"rrr",
	NULL
};

static void
	exec(t_ctx *ctx, int op)
{
	char	buf[5];
	size_t	size;

	size = 0;
	while (g_ops[op][size])
	{
		buf[size] = g_ops[op][size];
		size += 1;
	}
	buf[size] = '\n';
	size += 1;
	write(1, buf, size);
	c_exec(ctx, op);
}

static void
	split(t_ctx *ctx, size_t size, int op)
{
	while (size > 0)
	{
		exec(ctx, op_pb ^ op);
		size -= 1;
	}
}

static void
	merge(t_ctx *ctx, size_t size, int op, int sign)
{
	size_t	left;
	size_t	right;
	int		tmp;

	left = (size + 1) / 2;
	right = size / 2;
	while (left > 0)
	{
		exec(ctx, op_ra ^ op);
		left -= 1;
	}
	left = (size + 1) / 2;
	while (left > 0 || right > 0)
	{
		if (left == 0)
			tmp = 1;
		else if (right == 0)
			tmp = 0;
		else if ((ctx->stacks[op].last->value > ctx->stacks[1 - op].frst->value) == sign)
			tmp = 0;
		else if ((ctx->stacks[op].last->value < ctx->stacks[1 - op].frst->value) == sign)
			tmp = 1;
		if (tmp)
		{
			exec(ctx, op_pa ^ op);
			right -= 1;
		}
		else
		{
			exec(ctx, op_rra ^ op);
			left -= 1;
		}
	}
}

static void
	sort2(t_ctx *ctx, size_t size, int op, int sign)
{
	if ((ctx->stacks[op].frst->value > ctx->stacks[op].frst->next->value) == sign)
		exec(ctx, op_sa ^ op);
	if (size == 3 && (ctx->stacks[op].frst->next->value > ctx->stacks[op].frst->next->next->value) == sign)
	{
		exec(ctx, op_ra ^ op);
		if ((ctx->stacks[op].frst->value > ctx->stacks[op].frst->next->value) == sign)
			exec(ctx, op_sa ^ op);
		exec(ctx, op_rra ^ op);
		if ((ctx->stacks[op].frst->value > ctx->stacks[op].frst->next->value) == sign)
			exec(ctx, op_sa ^ op);
	}
}

void
	sort(t_ctx *ctx, size_t size, int op, int sign)
{
	if (size > 3)
	{
		split(ctx, size / 2, op);
		sort(ctx, (size + 1) / 2, op, sign);
		sort(ctx, size / 2, op ^ 1, 1 - sign);
		merge(ctx, size, op, sign);
	}
	else if (size > 1)
	{
		sort2(ctx, size, op, sign);
	}
}
