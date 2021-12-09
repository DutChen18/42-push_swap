#include "push_swap.h"

int
	op_swap(t_stack *stack, const char *op)
{
	t_list	*l1;
	t_node	*n1;
	t_node	*n2;

	if (op[1] == 's')
		return (op_swap(stack, "sa") && op_swap(stack, "sb"));
	else if (op[1] == 'a')
		l1 = &stack->a;
	else if (op[1] == 'b')
		l1 = &stack->b;
	else
		return (0);
	n1 = l_pop_frst(l1);
	n2 = l_pop_frst(l1);
	l_add_frst(l1, n1);
	l_add_frst(l1, n2);
	return (1);
}

int
	op_push(t_stack *stack, const char *op)
{
	t_list	*l1;
	t_list	*l2;
	t_node	*n1;

	if (op[1] == 'a')
	{
		l1 = &stack->a;
		l2 = &stack->b;
	}
	else if (op[1] == 'b')
	{
		l1 = &stack->b;
		l2 = &stack->a;
	}
	else
	{
		return (0);
	}
	n1 = l_pop_frst(l2);
	l_add_frst(l1, n1);
	return (1);
}

int
	op_shup(t_stack *stack, const char *op)
{
	t_list	*l1;
	t_node	*n1;

	if (op[1] == 'r')
		return (op_shup(stack, "ra") && op_shup(stack, "rb"));
	else if (op[1] == 'a')
		l1 = &stack->a;
	else if (op[1] == 'b')
		l1 = &stack->b;
	else
		return (0);
	n1 = l_pop_frst(l1);
	l_add_last(l1, n1);
	return (1);
}

int
	op_shdo(t_stack *stack, const char *op)
{
	t_list	*l1;
	t_node	*n1;

	if (op[2] == 'r')
		return (op_shdo(stack, "rra") && op_shdo(stack, "rrb"));
	else if (op[2] == 'a')
		l1 = &stack->a;
	else if (op[2] == 'b')
		l1 = &stack->b;
	else
		return (0);
	n1 = l_pop_last(l1);
	l_add_frst(l1, n1);
	return (1);
}

int
	op_exec(t_stack *stack, const char *op)
{
	if (op[0] == 's' && !op[2])
		return (op_swap(stack, op));
	else if (op[0] == 'p' && !op[2])
		return (op_push(stack, op));
	else if (op[0] == 'r' && !op[2])
		return (op_shup(stack, op));
	else if (op[0] == 'r' && op[1] == 'r' && !op[3])
		return (op_shdo(stack, op));
	else
		return (0);
}
