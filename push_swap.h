/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 10:32:31 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/17 10:32:32 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stddef.h>

# ifndef CHUNK_SIZE
#  define CHUNK_SIZE 150
# endif

typedef struct s_node	t_node;
typedef struct s_list	t_list;

struct s_node {
	t_node	*next;
	t_node	*prev;
	int		value;
};

struct s_list {
	t_node	*frst;
	t_node	*last;
	size_t	size;
};

enum {
	op_sa = 0x0,
	op_sb = 0x1,
	op_ss = 0x2,
	op_pa = 0x4,
	op_pb = 0x5,
	op_ra = 0x8,
	op_rb = 0x9,
	op_rr = 0xA,
	op_rra = 0xC,
	op_rrb = 0xD,
	op_rrr = 0xE
};

void	l_add_frst(t_list *list, t_node *node);
void	l_add_last(t_list *list, t_node *node);
t_node	*l_pop_frst(t_list *list);
t_node	*l_pop_last(t_list *list);

void	o_swap(t_list *ctx, int op);
void	o_push(t_list *ctx, int op);
void	o_shup(t_list *ctx, int op);
void	o_shdo(t_list *ctx, int op);
void	o_exec(t_list *ctx, int op);

int		u_max(int a, int b);
int		u_min(int a, int b);
int		u_abs(int a);
int		u_absmax(int a, int b);
int		u_absmin(int a, int b);

int		r_cost(int a, int b);
void	r_min(int *a1, int a2, int *b1, int b2);
void	r_optimize(int *r, int sa, int *rb, int sb);
void	r_rot(t_list *ctx, int o1, int o2, int count);
void	r_rotate(t_list *ctx, int a, int b);

int		i_parse(const char *buf);
int		i_read(int *op);
void	i_write(int op);
void	i_exec(t_list *ctx, int op);

int		a_position(t_list *list, int value);
int		a_select(t_list *list, int n);
int		a_min_index(t_list *list);

int		ps_main(t_list *ctx);

#endif
