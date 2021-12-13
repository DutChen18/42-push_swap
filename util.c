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

void
	u_exec(t_list *ctx, int w, int op)
{
	char	buf[4];
	size_t	size;

	if (w)
	{
		size = 0;
		while (g_ops[op][size])
		{
			buf[size] = g_ops[op][size];
			size += 1;
		}
		buf[size] = '\n';
		size += 1;
		write(1, buf, size);
	}
	o_exec(ctx, op);
}

void
	u_rotate(t_list *ctx, int w, int a, int b)
{
	while (a != 0 && b != 0 && (a < 0) == (b < 0))
	{
		u_exec(ctx, w, op_rr + (a < 0) * 4);
		a += (a < 0) - (a > 0);
		b += (b < 0) - (b > 0);
	}
	while (a != 0)
	{
		u_exec(ctx, w, op_ra + (a < 0) * 4);
		a += (a < 0) - (a > 0);
	}
	while (b != 0)
	{
		u_exec(ctx, w, op_rb + (b < 0) * 4);
		b += (b < 0) - (b > 0);
	}
}

int
	u_cost(int a, int b)
{
	if (a < 0 && b < 0)
		return ((a < b) * -a + (b <= a) * -b);
	else if (a > 0 && b > 0)
		return ((a > b) * a + (b >= a) * b);
	else
		return (a * (1 - (a < 0) * 2) + b * (1 - (b < 0) * 2));
}

void
	u_optimize(int *ra, int sa, int *rb, int sb)
{
	int	ta;
	int	tb;

	ta = *ra - sa;
	tb = *rb;
	if (u_cost(ta, tb) < u_cost(*ra, *rb))
	{
		*ra = ta;
		*rb = tb;
	}
	tb = tb - sb;
	if (u_cost(ta, tb) < u_cost(*ra, *rb))
	{
		*ra = ta;
		*rb = tb;
	}
	ta = ta + sa;
	if (u_cost(ta, tb) < u_cost(*ra, *rb))
	{
		*ra = ta;
		*rb = tb;
	}
}
