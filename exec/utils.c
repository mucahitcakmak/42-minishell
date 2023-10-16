/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/05 12:47:24 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**lst_redirect_combining(t_list *lst)
{
	int		k;
	char	**str;
	t_list	*iter;

	k = -1;
	iter = NULL;
	iter = lst;
	str = malloc(10000);
	while (iter)
	{
		str[++k] = iter->value;
		iter = iter->next;
	}
	str[++k] = 0;
	return (str);
}