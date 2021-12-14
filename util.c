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
