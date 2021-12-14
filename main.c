#include "push_swap.h"
#include <stdio.h>

void
	dump(t_list *list)
{
	t_node	*node;

	node = list->frst;
	while (node != NULL)
	{
		printf(" %d", node->value);
		node = node->next;
	}
	printf("\n");
}

int
	run(t_list *list)
{
	t_list	ctx[2];

	ctx[0] = *list;
	ctx[1].frst = NULL;
	ctx[1].last = NULL;
	ctx[1].size = 0;
	a_sort(ctx);
	dump(&ctx[0]);
	return (0);
}

int
	main(int argc, char **argv)
{
	t_list	list;

	(void) argc;
	list.frst = NULL;
	list.last = NULL;
	list.size = 0;
	i_init(argv + 1, &list, run);
}
