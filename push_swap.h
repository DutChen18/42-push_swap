#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stddef.h>

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

void	u_exec(t_list *ctx, int op);
void	u_rotate(t_list *ctx, int a, int b);
int		u_cost(int a, int b);
void	u_min(int *a1, int a2, int *b1, int b2);
void	u_optimize(int *ra, int sa, int *rb, int sb);

void	s_sort(t_list *ctx, int size);

#endif
