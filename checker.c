/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 10:31:55 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/17 12:43:22 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

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
	if (a_sorted(&ctx[0]) && ctx[1].size == 0)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	return (0);
}
