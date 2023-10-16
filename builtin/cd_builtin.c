/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:55:14 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/10 19:39:44 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_changer(t_list *lst)
{
	char *s;
	t_list	*tmp;

	tmp = lst;
	s = getcwd(NULL, 0);
	if (tmp && !ft_strcmp(tmp->key, "PWD") && s)
	{
		free(tmp->value);
		tmp->value = ft_strdup(s);
		free(s);
	}
}

void	old_pwd_and_pwd_changer(t_list *lst)
{
	t_list	*tmp;
	t_list	*pwd;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
			pwd = tmp;
			break;
		}
		else
			pwd = 0;
		tmp = tmp->next;
	}
	tmp = lst;
	while (tmp)
	{
		if (pwd && !ft_strcmp(tmp->key, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(pwd->value);
			break;
		}
		tmp = tmp->next;
	}
	pwd_changer(pwd);
}

char	*find_key_and_get_char(t_list *lst, char *s)
{
	t_list	*tmp;
	tmp = lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, s))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

t_list *and_get_lst(t_list *lst, char *s)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, s))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

int	set_home(t_data *info)
{
	char	*temp;

	if (!info->cmd->commands[1])
	{
		temp = find_key_and_get_char(info->env_lst, "HOME");
		if(temp && !chdir(temp))
		{
			old_pwd_and_pwd_changer(info->env_lst);
			old_pwd_and_pwd_changer(info->export_lst);
			return (1);
		}
		else
			printf("HOME not set\n");
		return (1);
	}
	return (0);
}

int	cd_builtin(t_data *info, char *rl)
{
	char	*s;

	if (!check_builtin_str(info, "cd"))
	{
		if (set_home(info))
		{
			free_info_and_rl(info, rl);
			info->exit_code = 0;
			return (1);
		}
		if (info->cmd->flags[1] == Q0)
			s = ft_strtrim(info->cmd->commands[1], " ");
		else
			s = ft_strdup(info->cmd->commands[1]);
		if (chdir(s))
		{
			info->exit_code = 1;
			printf("%s : No such file or directory\n", s);
		}
		else
		{
			old_pwd_and_pwd_changer(info->env_lst);
			old_pwd_and_pwd_changer(info->export_lst);
			info->exit_code = 0;
		}
		free_info_and_rl(info, rl);
		free(s);
		return (1);
	}
	return (0);
}
