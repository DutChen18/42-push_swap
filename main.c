#include "push_swap.h"
#include <stdio.h>

const char
	*ft_atoi(const char *str, int *value)
{
	int	sign;

	sign = 1 - (*str == '-') * 2;
	str += *str == '-';
	*value = 0;
	while (*str >= '0' && *str <= '9')
	{
		*value = *value * 10 + (*str - '0') * sign;
		str += 1;
	}
	return (str);
}

int
	init(char **argv, t_list *list, int (fn)(t_list *))
{
	t_node	node;

	if (*argv == NULL)
		return (fn(list));
	if (*ft_atoi(*argv, &node.value))
		return (-1);
	l_add_last(list, &node);
	return (init(argv + 1, list, fn));
}

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
	s_sort(ctx, ctx[0].size);
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
	init(argv + 1, &list, run);
}
