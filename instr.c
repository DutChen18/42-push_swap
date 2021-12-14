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
	i_parse(const char *buf)
{
	int	i;
	int	j;

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

int
	i_read(int *op)
{
	char	buf[4];
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = read(0, buf + i, 1);
		if (j == 0 && i == 0)
			return (0);
		if (j <= 0)
			return (-1);
		if (buf[i] == '\n')
			break ;
		i += 1;
	}
	i = i_parse(buf);
	if (i < 0)
		return (-1);
	*op = i;
	return (1);
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
