/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:04:17 by mucakmak          #+#    #+#             */
/*   Updated: 2023/09/27 18:37:30 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_ct(char *read_line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (read_line[i])
	{
		if (read_line[i] == '|')
			count++;
		i++;
	}
	return (count * 2);
}

char	*add_space(char *rd)
{
	int		i;
	int		j;
	char	*new_line;

	i = -1;
	j = 0;
	new_line = malloc((ft_strlen(rd) + pipe_ct(rd) + 1));
	while (rd[++i])
	{
		if (rd[i] == '|' || rd[i] == '<' || rd[i] == '>')
		{
			new_line[i + j++] = ' ';
			new_line[i + j] = rd[i];
			if ((rd[i] && rd[i + 1] && rd[i] == '>' && rd[i + 1] == '>'
					|| rd[i] == '<' && rd[i + 1] == '<')
				&& rd[++i])
				new_line[i + j] = rd[i];
			new_line[i + ++j] = ' ';
			continue ;
		}
		new_line[i + j] = rd[i];
	}
	new_line[i + j] = 0;
	return (new_line);
}

int	ft_char_count(char *read_line, int c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while(read_line[++i])
		if (read_line[i] == c)
			count++;
	return (count);
}

char	*lst_combining(t_data *info)
{
	int	i;
	char *p;
	int		k;

	k = -1;
	i = -1;
	p = malloc(10000);
	while (info->arg)
	{
		while (info->arg->value[++i])
		{
			p[++k] = info->arg->value[i];
		}
		i = -1;
		info->arg = info->arg->next;
	}
	p[++k] = 0;
	printf("lst / (%s)\n", p);
	return (p);
}

void	two_pointer_free(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}
