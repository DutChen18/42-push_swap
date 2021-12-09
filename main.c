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

int
	init(t_list *list, int argc, char **argv)
{
	int		i;
	int		tmp;
	t_node	*node;

	i = 0;
	list->frst = NULL;
	list->last = NULL;
	while (i < argc)
	{
		node = malloc(sizeof(*node));
		if (node != NULL)
		{
			l_add_last(list, node);
			tmp = *ft_atoi(argv[i], &node->value);
		}
		if (node == NULL || tmp)
		{
			while (list->frst != NULL)
				free(l_pop_frst(list));
			return (0);
		}
		i += 1;
	}
	return (1);
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
	t_stack	stack;

	init(&stack.a, argc - 1, argv + 1);
	stack.b.frst = NULL;
	stack.b.last = NULL;
	dump(stack.a, "a");
	dump(stack.b, "b");
	op_exec(&stack, "ra");
	dump(stack.a, "a");
	dump(stack.b, "b");
}
