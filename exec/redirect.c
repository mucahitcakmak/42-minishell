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

void	redirect_split(t_data *info, t_list **lst, char *s, int in)
{
	int	i;
	int tmp;
	t_list	*temp;

	i = 0;
	while (s[i])
	{
		tmp = i;
		while (s[i] && s[i] != '>' && s[i] != '<')
			i++;
		ft_lstadd_back(lst, ft_lstnew((void *)Q0, ft_substr(s, tmp, i - tmp)));

		tmp = i;
		while (s[i] && (s[i] == '>' || s[i] == '<'))
			i++;
		ft_lstadd_back(lst, ft_lstnew((void *)Q0, ft_substr(s, tmp, i - tmp)));
	}
}

void	lst_add_redirect(t_data *info, t_list **lst, int i)
{
	char **str;

	str = info->cmd->commands;
	while (str[i])
	{
		if (ft_char_count(str[i], '|') > 0 && (void *)(long)info->cmd->flags[i] == Q0)
			break ;
		if ((void *)(long)info->cmd->flags[i] == Q0 && (ft_char_count(str[i], '>') 
			|| ft_char_count(str[i], '<')))
			redirect_split(info, lst, str[i], i);
		else
			ft_lstadd_back(lst, ft_lstnew((void *)(long)info->cmd->flags[i], str[i]));
		i++;
	}
}

t_list	*go_redirect(t_list *lst)
{
	while (lst)
	{
		if (lst->key == Q0 && (ft_char_count(lst->value, 
			'>') || ft_char_count(lst->value, '<')))
				return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	output_redirection(t_data *info, t_list	*lst)
{
	int		fd;
	int		end;
	char	*s;
	t_list	*red;

	red = lst;
	lst = lst->next;
	if (lst->value[0] == ' ')
		lst = lst->next;
	if (!lst->value[0])
		lst = lst->next;
	if (lst->key == Q0)
		s = ft_strtrim(lst->value, " ");
	else
		s = ft_strdup(lst->value);
	free(lst->value);
	free(red);
	lst->value = ft_strdup("");
	red->value = ft_strdup("");
	fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
 	dup2(fd, 1);
	close(fd);
	free(s);
	return ;
}

void	lst_run_redirect(t_data *info, t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		tmp = go_redirect(tmp);
		if (tmp && tmp->next && ft_char_count(tmp->value, '>') == 1)
			output_redirection(info, tmp);
		if (tmp)
			tmp = tmp->next;
	}
}

char	**redirect(t_data *info, int count)
{
	int	j;
	t_list *lst;

	lst = NULL;
	lst_add_redirect(info, &lst, count);
	lst_run_redirect(info, &lst);
	return (lst_redirect_combining(lst));
}
 