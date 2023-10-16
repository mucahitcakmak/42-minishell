/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/08 10:03:12 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    check_n(t_data *info, char **s, int c)
{
    int i;

    if (s[1][0] != '-')
        return (0);
    if (s[1][0] == '-')
    {
        i = 1;
        while (s[1][i])
            if (s[1][i++] != 'n')
                return (0);
    }
    return (1);
}

void    echo(t_data *info, char **s, int c)
{
    int i;
    int flag;

    i = 1;
    flag = check_n(info, s, c);
    if (flag == 1)
        i++;
    while (s[i])
    {
        printf("%s", s[i++]);
        if (s[i])
            printf(" ");
    }
    if (flag == 0)
        printf("\n");
    exit(0);
}

void	builtin(t_data *info, char **s, int count)
{
    if (!ft_strcmp(s[0], "echo"))
        echo(info, s, count);
}