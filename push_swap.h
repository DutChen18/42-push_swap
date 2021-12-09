#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stddef.h>

typedef struct s_node	t_node;
typedef struct s_list	t_list;
typedef struct s_stack	t_stack;

struct s_node {
	t_node	*next;
	t_node	*prev;
	int		value;
};

struct s_list {
	t_node	*frst;
	t_node	*last;
};

struct s_stack {
	t_list	a;
	t_list	b;
};

void	l_add_frst(t_list *list, t_node *node);
void	l_add_last(t_list *list, t_node *node);
t_node	*l_pop_frst(t_list *list);
t_node	*l_pop_last(t_list *list);

int		op_swap(t_stack *stack, const char *op);
int		op_push(t_stack *stack, const char *op);
int		op_shup(t_stack *stack, const char *op);
int		op_shdo(t_stack *stack, const char *op);
int		op_exec(t_stack *stack, const char *op);

#endif
