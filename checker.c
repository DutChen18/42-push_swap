#include "push_swap.h"
#include <unistd.h>

static int
	sorted(t_list *list)
{
	t_node	*node;

	node = list->frst;
	while (node != NULL && node->next != NULL)
	{
		if (node->value > node->next->value)
			return (0);
		node = node->next;
	}
	return (1);
}

int
	ps_main(t_list *ctx)
{
	int	op;
	int	tmp;

	while (1)
	{
		tmp = i_read(&op);
		if (tmp < 0)
			return (-1);
		if (tmp == 0)
			break ;
		o_exec(ctx, op);
	}
	if (sorted(&ctx[0]) && ctx[1].size == 0)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	return (0);
}
