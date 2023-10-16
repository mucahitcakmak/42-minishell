/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/10 18:40:32 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_is_path(t_data *info, char *s, char *p)
{
	if (!ft_strcmp(s, "PATH"))
	{
		two_pointer_free(info->paths);
		info->paths = ft_split(p, ':');
		int i = -1;
		while (info->paths[++i])
			printf("pathmi: (%s)\n", info->paths[i]);
	}
}

void    export_builtin(t_data *info)
{
    t_list  *exlst;

    exlst = info->export_lst;
    while (exlst)
    {
        printf("declare -x ");
        printf("%s=\"%s\"\n", exlst->key, exlst->value);
        exlst = exlst->next;
    }
    exit(0);
}

void	change_export(t_data *info, char *s)
{
	char	*tmp;
	char	*tmp2;

	if (ft_char_count(s, '='))
	{
		tmp = ft_substr(s, 0, find_i(s, '='));
		tmp2 = ft_substr(s, find_i(s, '=') + 1, 
			ft_strlen(s) - find_i(s, '=') + 1);
		export_control_and_change(info->env_lst, tmp, tmp2, 1);
		tmp = ft_substr(s, 0, find_i(s, '='));
		tmp2 = ft_substr(s, find_i(s, '=') + 1, 
			ft_strlen(s) - find_i(s, '=') + 1);
		export_control_and_change(info->export_lst, tmp, tmp2, 1);
		export_is_path(info, tmp, tmp2);
	}
	else
		export_control_and_change(info->export_lst, s, ft_strdup(""), 0);
}

int	export_syntax(t_data *info)
{
	int		i;
	t_list	*tlst;
	char **s;

	i = 0;
	tlst = NULL;
	while (info->cmd->commands[++i])
		ft_lstadd_back(&tlst, ft_lstnew((void *)(long)info->cmd->flags[i], info->cmd->commands[i]));
	s = lst_redirect_combining(tlst);
	i = -1;
	while (s[++i])
		if (ft_char_count(s[i], '='))
			if (find_i(s[i], '=') == 0)
				return (err_message(info, "Syntax Error"));
	i = -1;
	while (s[++i])
		change_export(info, s[i]);
	return (0);
}

void    env_builtin(t_data *info)
{
    t_list  *envlst;

    envlst = info->env_lst;
    while (envlst)
    {
        printf("%s=%s\n", envlst->key, envlst->value);
        envlst = envlst->next;
    }
    exit(0);
}


int	export_control_and_change(t_list *info, char *s, char *p, int i)
{
	int		j;
	t_list *tmp;

	tmp = info;
	while (tmp)
	{
		if (!ft_strcmp((const char *)tmp->key, s))
		{
			if (i)
			{
				free(tmp->value);
				tmp->value = ft_strdup(p);
			}
			return (0);
		}
		tmp = tmp->next;
	}
	ft_lstadd_back(&info, ft_lstnew(s, p));
	return (1);
}

int    add_export(t_data *info, char *rl)
{
	char	**s;
	t_list	*tmp;

	tmp = info->env_lst;
    if (!check_builtin_str(info, "export") && info->cmd->commands[1])
	{
		export_syntax(info);
        free_info_and_rl(info, rl);
		info->exit_code = 0;
    	return (1);
	}
    return (0);
}
