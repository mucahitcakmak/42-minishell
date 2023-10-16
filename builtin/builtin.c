/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/10 08:08:46 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_builtin_str(t_data *info, char *str)
{
    char    *s;

    if (info->cmd->flags[0] == Q0)
    {
        s = ft_strtrim(info->cmd->commands[0], " ");
        if (!ft_strcmp(s, str))
        {
            free(s);
            return (0);
        }
        free(s);
    }
    else
        if (!ft_strcmp(info->cmd->commands[0], str))
            return (0);
    return (1);
}

int main_builtin(t_data *info, char *rl)
{
    if (add_export(info, rl))
        return (1);
	if (exit_builtin(info, rl))
		return (1);
    return (0);
}

void	child_builtin(t_data *info, char **s, int count)
{
    if (!ft_strcmp(s[0], "echo"))
        echo_builtin(info, s, count);
    else if (!ft_strcmp(s[0], "export"))
        export_builtin(info);
	else if (!ft_strcmp(s[0], "env"))
		env_builtin(info);
}
