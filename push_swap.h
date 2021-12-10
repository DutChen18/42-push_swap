#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stddef.h>

typedef struct s_node	t_node;
typedef struct s_list	t_list;
typedef struct s_ctx	t_ctx;

struct s_node {
	t_node	*next;
	t_node	*prev;
	int		value;
};

struct s_list {
	t_node	*frst;
	t_node	*last;
};

struct s_ctx {
	t_list	stacks[2];
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

void	c_swap(t_ctx *ctx, int op);
void	c_push(t_ctx *ctx, int op);
void	c_shup(t_ctx *ctx, int op);
void	c_shdo(t_ctx *ctx, int op);
void	c_exec(t_ctx *ctx, int op);

void	sort(t_ctx *ctx, size_t size, int op, int sign);

#endif
