/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/08 11:49:17 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_exit(t_data *info)
{
    char    *s;

    if (info->cmd->flags[0] == Q0)
    {
        s = ft_strtrim(info->cmd->commands[0], " ");
        if (!ft_strcmp(s, "exit"))
        {
            free(s);
            return (0);
        }
        free(s);
    }
    else
        if (!ft_strcmp(info->cmd->commands[0], "exit"))
            return (0);
    return (1);
}

int    exit_builtin(t_data *info, char *rl)
{
    int i;
    int status;

    printf("exit mi (%d)\n", check_exit(info));
    if (check_exit(info))
        return (0);
    i = 0;
    status = ft_atoi(info->cmd->commands[1]);
    while (info->cmd->commands[i])
        i++;
    if (i > 2)
    {
        printf("Too many arguments\n");
        return (free_info_and_rl(info, rl));
    }
    printf("exit\n");
    if (i == 2)
        exit(status);
    exit(127);
}
