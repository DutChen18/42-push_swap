#include "push_swap.h"

int
	r_cost(int a, int b)
{
	if (a < 0 && b < 0)
		return (-u_min(a, b));
	if (a > 0 && b > 0)
		return (u_max(a, b));
	return (u_abs(a) + u_abs(b));
}

void
	r_min(int *a1, int a2, int *b1, int b2)
{
	if (r_cost(a2, b2) < r_cost(*a1, *b1))
	{
		*a1 = a2;
		*b1 = b2;
	}
}

void
	r_optimize(int *ra, int sa, int *rb, int sb)
{
	int	ta;
	int	tb;

	ta = *ra;
	tb = *rb;
	r_min(ra, ta - sa, rb, tb);
	r_min(ra, ta, rb, tb - sb);
	r_min(ra, ta - sa, rb, tb - sb);
}

void
	r_rot(t_list *ctx, int o1, int o2, int count)
{
	while (count > 0)
	{
		i_exec(ctx, o1);
		count -= 1;
	}
	while (count < 0)
	{
		i_exec(ctx, o2);
		count += 1;
	}
}

void
	r_rotate(t_list *ctx, int a, int b)
{
	int	i;

	i = 0;
	if (a < 0 && b < 0)
		i = u_min(a, b);
	if (a > 0 && b > 0)
		i = u_max(a, b);
	r_rot(ctx, op_rr, op_rrr, i);
	r_rot(ctx, op_ra, op_rra, a - i);
	r_rot(ctx, op_rb, op_rrb, b - i);
}
