/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/07 19:50:28 by museker          ###   ########.fr       */
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

char	*rd_last_str(t_list	*lst)
{
	char	*s;
	t_list	*red;

	red = lst;
	lst = lst->next;
	if (lst->value[0] == ' ' && lst->key == Q0)
		lst = lst->next;
	if (!lst->value[0])
		lst = lst->next;
	if (lst->key == Q0)
		s = ft_strtrim(lst->value, " ");
	else
		s = ft_strdup(lst->value);
	free(lst->value);
	free(red->value);
	lst->value = ft_strdup("");
	red->value = ft_strdup("");
	return (s);
}


void	overwrite_output(t_data *info, t_list	*lst)
{
	int		fd;
	char	*s;

	s = rd_last_str(lst);
	fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
 	dup2(fd, 1);
	close(fd);
	return ;
}

void	append_output(t_data *info, t_list	*lst)
{
	int		fd;
	char	*s;

	s = rd_last_str(lst);
	fd = open(s, O_WRONLY | O_CREAT | O_APPEND, 0644);
 	dup2(fd, 1);
	close(fd);
	return ;
}

void	overwrite_input(t_data *info, t_list	*lst)
{
	int		fd;
	char	*s;

	s = rd_last_str(lst);
	fd = open(s, O_RDONLY, 0644);
 	dup2(fd, 0);
	close(fd);
	return ;
}

void	append_input(t_data *info, t_list	*lst)
{
	char	*s;
	char	*rd;
	int		fd;
	static int counter = 0;

	counter++;
	s = rd_last_str(lst);
	fd = open(s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (counter == 2)
		dup2(fd,1);
	while (1)
	{
		rd = readline("> ");
		if (!ft_strcmp(rd, s))
			break; 
	}
	close(fd);
	pipe_close(info);
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
			overwrite_output(info, tmp);
		else if (tmp && tmp->next && ft_char_count(tmp->value, '>') == 2)
			append_output(info, tmp);
		else if (tmp && tmp->next && ft_char_count(tmp->value, '<') == 1)
			overwrite_input(info, tmp);
		else if (tmp && tmp->next && ft_char_count(tmp->value, '<') == 2)
			append_input(info, tmp);
		if (tmp)
			tmp = tmp->next;
	}
}
char	**ft_abc(t_data *info, char **s, int count)
{
	int	i;
	char	**p;
	int	j;
	int	k;
	int	l;

	p = malloc(sizeof(char *) * 1000);
	j = -1;
	i = -1;
	k = 0;
	while (s[++i])
	{
		if (!s[i][0] ||
			(s[i][0] == ' ' && info->cmd->flags[count + i] == Q0))
			continue ;
		if (!ft_strchr(s[i], ' '))
			p[k++] = ft_strdup(s[i]);
		else
		{
			if (info->cmd->flags[count + i] == Q1)
				p[k++] = ft_strdup(s[i]);
			else
				p[k++] = ft_substr(s[i], 0, ft_find_index(s[i], ' '));
		}
	}
	p[k] = NULL;
	return (p);
}

char	**redirect(t_data *info, int count)
{
	int	j;
	t_list *lst;
	char	**str;

	lst = NULL;

	lst_add_redirect(info, &lst, count);
	// lst_run_redirect(info, &lst);

	str = lst_redirect_combining(lst);
	return (str);
}
 
// ech"o" <<merhaba >> arkadalasr > b"e"n 'muco'
// lst: (ech)
// lst: (o)
// lst: ( )
// lst: ()
// lst: (<<)
// lst: (merhaba )
// lst: ()
// lst: ()
// lst: (>>)
// lst: ( )
// lst: ()
// lst: (arkadalasr )
// lst: ()
// lst: (>)
// lst: ( )
// lst: ()
// lst: (b)
// lst: (e)
// lst: (n )
// lst: (muco)