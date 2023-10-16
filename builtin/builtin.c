/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/07 19:54:07 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    check_n(t_data *info, char **s, int c)
{
    int i;

    i = 0;
    if (s[1][i] == '-' && info->cmd->flags[c + 1] == Q0)
    {
        while (s[1][i++] || s[1][i] != ' ')
            if (s[1][i] != 'n')
                return (1);
    }
    return (0);
}

void    echo(t_data *info, char **s, int c)
{
    int i;
    int flag;

    i = 1;
    // flag 1 ise -n çalışmayacak
    flag = check_n(info, s, c);
    if (flag == 1)
        i++;
    while (s[i])
    {
        printf("%s", s[i++]);
        if (s[i + 1])
            printf(" ");
    }
    if (flag == 0)
        printf("\n");
    exit(1);
}

void	builtin(t_data *info, char **s, int count)
{
    if (!ft_strcmp(s[0], "echo"))
        echo(info, s, count);
}