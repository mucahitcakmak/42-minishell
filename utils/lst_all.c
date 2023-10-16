#include "../minishell.h"

t_list	*ft_lstnew(void *key, void *value)
{
	t_list	*p;

	p = malloc(sizeof(t_list));
	if (!p)
		return (NULL);
	p->key = (char *)key;
	p->value = (char *)value;
	p->next = NULL;
	return (p);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*start;

	if (!lst || !new)
		return ;
	start = *lst;
	new->next = start;
	*lst = new;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	while (tmp-> next)
		tmp = tmp-> next;
	tmp->next = new;
}
