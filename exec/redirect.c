/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/05 03:21:42 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	overwrite_redirection(t_data *info)
{
	
}

void	go_redirect(char **str, int *i, int *j, char *s)
{
	while (str[*i][*j])
	{
		if (str[*i][*j] == '>' || str[*i][*j] == '<')
			break ;
		j++;
	}
}

// bunun gibi pipe ve redirect arasında hiç bir şey yoksa hata olarak döndürmeli
// cat b.txt > >  a.txt 
void	redirect(t_data *info, char **str, int i)
{
	int	j;

	j = 0;
	while (str[++i])
	{// sdfs >
		go_redirect(str, &i, &j, "<");
		if (str[i][j] == '>' && str[i][j + 1] == '>') // append output
			;
		else if (str[i][j] == '<' && str[i][j + 1] == '<') // append input
			;
		else if (str[i][j] == '<') // overwrite input
			;
		else if (str[i][j] == '>') // overwrite output
			;
	}
}
 