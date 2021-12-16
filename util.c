#include "push_swap.h"

int
	u_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int
	u_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int
	u_abs(int a)
{
	if (a > 0)
		return (a);
	else
		return (-a);
}

int
	u_absmax(int a, int b)
{
	if (u_abs(a) > u_abs(b))
		return (a);
	else
		return (b);
}

int
	u_absmin(int a, int b)
{
	if (u_abs(a) < u_abs(b))
		return (a);
	else
		return (b);
}
