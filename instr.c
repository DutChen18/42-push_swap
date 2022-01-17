/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   instr.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 10:31:57 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/17 10:31:59 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

static const char
	*get_op(int i)
{
	const char	*ops[16] = {
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

	return (ops[i]);
}

int
	i_parse(const char *buf)
{
	int	i;
	int	j;

	i = 0;
	while (i < 16)
	{
		if (get_op(i) != NULL)
		{
			j = 0;
			while (get_op(i)[j] && get_op(i)[j] == buf[j])
				j += 1;
			if (!get_op(i)[j] && buf[j] == '\n')
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
	char	buf[4];
	size_t	size;

	size = 0;
	while (get_op(op)[size])
	{
		buf[size] = get_op(op)[size];
		size += 1;
	}
	buf[size] = '\n';
	size += 1;
	write(1, buf, size);
}

void
	i_exec(t_list *ctx, int op)
{
	i_write(op);
	o_exec(ctx, op);
}
