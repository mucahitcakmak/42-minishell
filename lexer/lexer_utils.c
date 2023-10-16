/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:04:17 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/04 18:07:25 by mucakmak         ###   ########.fr       */
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
	while (read_line[++i])
		if (read_line[i] == c)
			count++;
	return (count);
}

char	**pipe_split(char	*s, char c, int p)
{
	int		i;
	int		j;
	int		temp;
	char	**str_split;

	i = 0;
	j = 0;
	str_split = (char **)malloc(sizeof(char *) * (count_word(s, c) + p + 1));
	if (!str_split)
		return (NULL);
	while (s[i])
	{
		if (s[i] && s[i] == c && ++i)
			str_split[j++] = ft_strdup("|");
		temp = i;
		while (s[i] && s[i] != c)
			i++;
		if (count_word(s, c) + p == j)
			break ;
		str_split[j++] = ft_substr(s, temp, i - temp);
		if (s[i])
			i++;
		if (count_word(s, c) + p != j)
			str_split[j++] = ft_strdup("|");
	}
	str_split[j] = 0;
	return (str_split);
}

void	pipe_adder(t_data *info, char *str, int *k)
{
	int		i;
	char	**split;

	i = -1;
	split = pipe_split(str, '|', ft_char_count(str, '|'));
	while (split[++i])
	{
		info->cmd->commands[++(*k)] = split[i];
		info->cmd->flags[*k] = Q0;
	}
	free(split);
}

void	lst_combining(t_data *info)
{
	int		k;

	k = -1;
	info->cmd->commands = malloc(10000);
	info->cmd->flags = malloc(sizeof(int) * 10000);
	while (info->arg)
	{
		if (ft_char_count(info->arg->value, '|') && (int)(info->arg->key) == Q0)
			pipe_adder(info, info->arg->value, &k);
		else
		{
			info->cmd->commands[++k] = info->arg->value;
			info->cmd->flags[k] = (int)info->arg->key;
		}
		info->arg = info->arg->next;
	}
	info->cmd->commands[++k] = 0;
	info->cmd->flags[k] = 0;
}

void	two_pointer_free(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}
