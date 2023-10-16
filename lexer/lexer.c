/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:46 by museker           #+#    #+#             */
/*   Updated: 2023/09/27 19:13:37 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**lexer(t_data *info, char *read_line)
{
	char *tmp;
	char *new;
	char **split;

	quote(info, read_line);
	tmp = lst_combining(info);
	// new = add_space(tmp);
	// free(tmp);
	split = ft_split(tmp, ' ');
	return (split);
}

void	quote(t_data *info, char *read_line)
{
    int	i;

    i = 0;
	info->arg = NULL;
    while (read_line[i])
	{
		if (read_line[i] == 39)
			quotes(info, read_line, &i, 39);
		else if (read_line[i] == 34)
			quotes(info, read_line, &i, 34);
		else if (read_line[i] != 34 || read_line[i] != 39)
			no_quote(info, read_line, &i);
	}
}

void	quotes(t_data *info, char *read_line, int *index, int c1)
{
	int	i;
	int	start;
	char *new_line;
	char *maybe;
	int	end;
	t_list *tmplst;

	start = ++(*index);
	while (read_line[*index])
	{
		if (read_line[*index] == c1)
		{
			end = (*index)++;
			break;
		}
		(*index)++;
	}
	new_line = ft_substr(read_line, start, end - start);
	if (c1 == '"' && ft_char_count(new_line, '$'))
		ft_lstadd_back(&(info->arg), ft_lstnew(0, check_dollar(info, new_line)));
	else
		ft_lstadd_back(&(info->arg), ft_lstnew(0, new_line));
}

void	no_quote(t_data *info, char *read_line, int *index)
{
	int	i;
	int	start;
	char *new_line;
	int	end;
	t_list	*tmplst;

	start = *index;
	while (read_line[*index])
	{
		if (read_line[*index] == '\'' || read_line[*index] == '"')
		{
			end = *index;
			break;
		}
		(*index)++;
	}
	if (read_line[*index] == '\0' && !(read_line[*index - 1] == '\'' || read_line[*index - 1] == '"'))
		end = *index;
	new_line = ft_substr(read_line, start, end - start);
	ft_lstadd_back(&(info->arg), ft_lstnew(0, check_dollar(info, new_line)));
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
