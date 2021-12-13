#include "push_swap.h"

void
	l_add_frst(t_list *list, t_node *node)
{
	if (node == NULL)
		return ;
	node->next = list->frst;
	node->prev = NULL;
	if (list->frst != NULL)
		list->frst->prev = node;
	else
		list->last = node;
	list->frst = node;
	list->size += 1;
}

void
	l_add_last(t_list *list, t_node *node)
{
	if (node == NULL)
		return ;
	node->prev = list->last;
	node->next = NULL;
	if (list->last != NULL)
		list->last->next = node;
	else
		list->frst = node;
	list->last = node;
	list->size += 1;
}

t_node
	*l_pop_frst(t_list *list)
{
	t_node	*node;

	node = list->frst;
	if (node == NULL)
		return (NULL);
	list->frst = node->next;
	if (node->next != NULL)
		node->next->prev = NULL;
	else
		list->last = NULL;
	list->size -= 1;
	return (node);
}

t_node
	*l_pop_last(t_list *list)
{
	t_node	*node;

	node = list->last;
	if (node == NULL)
		return (NULL);
	list->last = node->prev;
	if (node->prev != NULL)
		node->prev->next = NULL;
	else
		list->frst = NULL;
	list->size -= 1;
	return (node);
}
