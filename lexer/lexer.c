/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:46 by museker           #+#    #+#             */
/*   Updated: 2023/10/04 18:07:28 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer(t_data *info, char *read_line)
{
	quote(info, read_line);
	lst_combining(info);
	// int i =-1;
	// char **tmp;
	// tmp = info->cmd->commands;
	// while (tmp[++i])
	// 	printf("DENEME: (%s)\n",tmp[i]);
}

void	quote(t_data *info, char *read_line)
{
    int	i;

    i = 0;
	info->arg = NULL;
    while (read_line[i])
	{
		if (read_line[i] == 39)
		{
			quotes(info, read_line, &i, 39);
		}
		else if (read_line[i] == 34)
			quotes(info, read_line, &i, 34);
		else if (read_line[i] != 34 || read_line[i] != 39)
		{
			no_quote(info, read_line, &i);
		}
	}
}

void	quotes(t_data *info, char *rl, int *index, int c1)
{
	int		start;
	char	*nl;
	int		end;

	start = ++(*index);
	while (rl[*index])
	{
		if (rl[*index] == c1)
		{
			end = (*index)++;
			break;
		}
		(*index)++;
	}
	nl = ft_substr(rl, start, end - start);
	if (c1 == '"' && ft_char_count(rl, '$'))
		ft_lstadd_back(&(info->arg), ft_lstnew((void *)Q2, check_dollar(info, nl)));
	else
		ft_lstadd_back(&(info->arg), ft_lstnew((void *)Q1, nl));
}

void	no_quote(t_data *info, char *rl, int *index)
{
	int		start;
	char	*nw_l;
	char 	*tmp;
	int		end;

	start = *index;
	while (rl[*index])
	{
		if (rl[*index] == '\'' || rl[*index] == '"' || rl[*index] == ' ')
		{
			if (rl[*index] == ' ')
				(*index)++;
			end = *index;
			while (rl[*index] == ' ')
				(*index)++;
			break ;
		}
		(*index)++;
	}
	if (rl[*index - 1] != ' ' && (rl[*index] == '\0'
			&& !(rl[*index - 1] == '\'' || rl[*index - 1] == '"')))
		end = *index;
	nw_l = ft_substr(rl, start, end - start);
	tmp = check_dollar(info, nw_l);
	ft_lstadd_back(&(info->arg), ft_lstnew((void *)Q0, tmp));
}

char	*char_combining(char **s)
{
	int		i;
	char	*p;
	int		count;
	int		j;
	int		k;

	i = -1;
	k = -1;
	count = 0;
	while (s[++i])
		count += ft_strlen(s[i]);
	i = -1;
	p = malloc(count + 1);
	while (s[++i])
	{
		j = -1;
		while (s[i][++j])
			p[++k] = s[i][j];
	}
	p[++k] = 0;
	return (p);
}
