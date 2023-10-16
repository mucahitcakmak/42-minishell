/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/07 19:53:39 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_index(char *s, int c, int q)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == c && q == Q0)
			return (i);
	return (i);
}

t_list	*new_lst(t_list *lst)
{
	int		i;
	int		j;
	int		tmp;

	i = -1;
	while (lst)
	{
		j = -1;
		tmp = get_index(lst->value, ' ', (int)lst->key);
		while (lst->value[++j] && j < tmp)
			i++;
		if (lst->value[j] == ' ' && lst->key == Q0)
			break ;
		lst = lst->next;
	}
	return (lst);
}

char	*get_str(t_list *lst)
{
	int		i;
	int		j;
	int		tmp;
	char	*s;

	i = -1;
	s = malloc(10000);
	while (lst)
	{
		j = -1;
		tmp = get_index(lst->value, ' ', (int)lst->key);
		while (lst->value[++j] && j < tmp)
			s[++i] = lst->value[j];
		if (lst->value[j] == ' ' && lst->key == Q0) // bekle ama bir şeyi daha yapıcam
			break ;
		lst = lst->next;
	}
	s[++i] = 0;
	return (s);
}

char	**lst_redirect_combining(t_list *lst)
{
	int		k;
	char	**str;
	t_list	*tmp;

	k = -1;
	str = malloc(sizeof(char *) * 100000);
	while (lst)
	{
		if (!lst->value[0])
		{
			lst = lst->next;
			continue ;
		}
		str[++k] = get_str(lst);
		lst = new_lst(lst);
		if (!lst)
			break;
		lst = lst->next;
	}
	str[++k] = 0;
	// k = -1;
	// while (str[++k])
	// 	printf("str:: (%s)\n", str[k]);
	return (str);
}