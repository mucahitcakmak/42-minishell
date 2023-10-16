/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:23 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/10 01:38:01 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    echo_check_n(t_data *info, char **s, int c)
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

void    echo_builtin(t_data *info, char **s, int c)
{
    int i;
    int flag;

    i = 1;
	if (!s[1])
	{
		printf("\n");
		exit(0);
	}
    flag = echo_check_n(info, s, c);
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
