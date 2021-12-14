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

int
	i_read(void)
{
	char	buf[4];
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		if (read(0, buf + i, 1) <= 0)
			break ;
		i += 1;
	}
	i = 0;
	while (i < 16)
	{
		if (g_ops[i] != NULL)
		{
			j = 0;
			while (g_ops[i][j] && g_ops[i][j] == buf[j])
				j += 1;
			if (!g_ops[i][j] && buf[j] == '\n')
				return (i);
		}
		i += 1;
	}
	return (-1);
}

void
	i_write(int op)
{
	const char	*str;

	str = g_ops[op];
	while (*str)
	{
		write(1, str, 1);
		str += 1;
	}
	write(1, "\n", 1);
}

void
	i_exec(t_list *ctx, int op)
{
	i_write(op);
	o_exec(ctx, op);
}

char
	*i_atoi(char *str, int *value)
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
	i_init(char **argv, t_list *list, int (fn)(t_list *))
{
	t_node	node;

	if (*argv == NULL)
		return (fn(list));
	if (*i_atoi(*argv, &node.value))
		return (-1);
	l_add_last(list, &node);
	return (i_init(argv + 1, list, fn));
}
