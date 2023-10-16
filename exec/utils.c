/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/06 17:08:58 by museker          ###   ########.fr       */
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
		if (iter->value[0])
			str[++k] = iter->value;
		iter = iter->next;
	}
	str[++k] = 0;
	return (str);
}