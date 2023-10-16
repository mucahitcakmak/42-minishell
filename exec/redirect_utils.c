/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:06:32 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/16 15:05:39 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	overwrite_output(t_data *info, t_list *lst)
{
	int		fd;
	char	*s;

	(void)info;
	s = rd_last_str(lst);
	fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 1);
	close(fd);
	return ;
}

void	append_output(t_data *info, t_list *lst)
{
	int		fd;
	char	*s;

	(void)info;
	s = rd_last_str(lst);
	fd = open(s, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, 1);
	close(fd);
	return ;
}

void	overwrite_input(t_data *info, t_list *lst)
{
	int		fd;
	char	*s;

	(void)info;
	s = rd_last_str(lst);
	fd = open(s, O_RDONLY, 0644);
	dup2(fd, 0);
	close(fd);
	return ;
}

void	append_input(t_data *info, t_list *lst, int i)
{
	char		*s;
	char		*rd;
	static int	counter = 0;

	counter++;
	s = rd_last_str(lst);
	signal(SIGINT, ft_sig_handler);
	while (1)
	{
		if (g_data->hd->flag)
			break ;
		rd = readline("> ");
		if (!ft_strcmp(rd, s))
			break ;
		if (counter == info->hd->flag)
		{
			ft_putstr_fd(rd, info->hd[i].fd[1]);
			ft_putchar_fd('\n', info->hd[i].fd[1]);
		}
	}
	if (counter == info->hd[i].flag)
		close(info->hd[i].fd[1]);
	return ;
}

void	lst_run_redirect(t_data *info, t_list **lst, int i)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		tmp = go_redirect(tmp);
		if (tmp && tmp->next && char_c(tmp->value, '>') == 1)
			overwrite_output(info, tmp);
		else if (tmp && tmp->next && char_c(tmp->value, '>') == 2)
			append_output(info, tmp);
		else if (tmp && tmp->next && char_c(tmp->value, '<') == 1)
			overwrite_input(info, tmp);
		else if (tmp && tmp->next && char_c(tmp->value, '<') == 2)
			append_input(info, tmp, i);
		if (tmp)
			tmp = tmp->next;
	}
}
