/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:43 by museker           #+#    #+#             */
/*   Updated: 2023/09/28 02:36:26 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_dollar(t_data *info, char *s)
{
	int		i;
	int		z;
	char	**new;
	char	*temp;

	i = 0;
	z = -1;
	new = malloc(sizeof(char *) * (ft_strlen(s) + 1));
	while (s[i])
	{
		if (s[i] == '$')
			temp = dollar_split(info, s, &i);
		else
			temp = no_dollar_split(s, &i);
		new[++z] = temp;
	}
	new[++z] = 0;
	char *km = char_combining(new);
	two_pointer_free(new);
	return (km);
}

void	*dollar_split2(t_data *info, char *s, int *in, int *tmp)
{
	char *char1;
	char *char_tmp;

	char_tmp = ft_substr(s, tmp[0], *in - tmp[0]);
	if (s[ft_strlen(s) - 1] != '$' && s[ft_strlen(s) - 1] != ' ' && s[ft_strlen(s) - 2] == '$')
		char1 = ft_substr(s, tmp[1], tmp[0] - tmp[1] - 1);
	else if (s[tmp[0] + 1] == '\0' || s[tmp[1] + 1] == '\0' || (s[*in] == '\0' && s[tmp[0] + 1] == '\0'))
		char1 = ft_substr(s, tmp[1], tmp[0] - tmp[1]);
	else if (find_key(info , char_tmp) || s[tmp[1] + 1] != ' ')
		char1 = ft_substr(s, tmp[1], tmp[0] - tmp[1] - 1);
	else
		char1 = ft_substr(s, tmp[1], tmp[0] - tmp[1]);
	free(char_tmp);
	return(char1);
}

void	*dollar_split(t_data *info, char *s, int *in)
{
	int		tmp[2];
	char	*char_tmp;
	char	*char1;
	char	*char2;

	tmp[1] = *in; // in = $
	while (s[*in] && s[*in] == '$')
		(*in)++;
	tmp[0] = *in;
	while (s[*in] && (s[*in] != '$' && (s[*in] != ' ')))
		(*in)++;
	char1 = dollar_split2(info, s, in, tmp);
	char_tmp = ft_substr(s, tmp[0], *in - tmp[0]);
	char2 = replace_dollar(info, char_tmp);
	char *char3 = ft_strjoin(char1, char2);
	free(char_tmp);
	free(char1);
	free(char2);
	return (char3);
}

void	*no_dollar_split(char *s, int *in)
{
	char 	*new;
	int		cpy_in;

	cpy_in = *in;
	while (s[cpy_in++])
		if (s[cpy_in] == '$' || s[cpy_in] == ' ')
			break ;
	new = ft_substr(s, *in, cpy_in - *in);
	*in = cpy_in;
	return (new);
}

char	*replace_dollar(t_data *info, char *s)
{
	t_list	*temp;
	char	*temp_str;

	temp = info->env_lst;
	while (temp)
	{
		if (ft_strnstr(temp->key, s,
			ft_strlen(s)))
		{
			temp_str = ft_strdup(temp->value);
			return (temp_str);
		}
		temp = temp->next;
	}
	if (!temp)
		return(ft_strdup(""));
	temp_str = ft_strdup(s);
	return (temp_str);
}
