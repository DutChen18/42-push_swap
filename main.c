#include "push_swap.h"
#include <stdlib.h>
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

t_node
	*init(t_list *list, int argc, char **argv)
{
	int		i;
	t_node	*nodes;

	i = 0;
	list->frst = NULL;
	list->last = NULL;
	nodes = malloc(sizeof(*nodes) * argc);
	if (nodes == NULL)
		return (NULL);
	while (i < argc)
	{
		l_add_last(list, &nodes[i]);
		if (*ft_atoi(argv[i], &nodes[i].value))
		{
			free(nodes);
			return (NULL);
		}
		i += 1;
	}
	return (nodes);
}

void
	dump(t_list list, const char *name)
{
	t_node	*node;

	node = list.last;
	printf("%s>", name);
	while (node != NULL)
	{
		printf(" %d", node->value);
		node = node->prev;
	}
	printf("\n");
}

int
	main(int argc, char **argv)
{
	t_ctx	ctx;

	init(&ctx.stacks[0], argc - 1, argv + 1);
	ctx.stacks[1].frst = NULL;
	ctx.stacks[1].last = NULL;
	dump(ctx.stacks[0], "a");
	dump(ctx.stacks[1], "b");
	sort(&ctx, argc - 1, 0, 1);
	dump(ctx.stacks[0], "a");
	dump(ctx.stacks[1], "b");
}
