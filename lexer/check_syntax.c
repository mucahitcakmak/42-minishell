/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:04:17 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/10 18:43:40 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    err_message(t_data *info, char *msg)
{
    int fd;

    fd = fork();
    if (fd == 0)
    {
        printf("%s\n", msg);
        exit(1);
    }
    else
        wait(&fd);
	info->exit_code = 1;
    return (1);
}

int    go_next_qoute(char *r, int *i)
{
    while (r[*i])
    {
        if (r[*i] == '\'')
        {
            (*i)++;
            while (r[*i] && r[*i] != '\'')
                (*i)++;
            if (r[*i] == '\'' && (*i)++)
                return (0);
            else
                return (1);
        }
        else if (r[*i] == '"')
        {
            (*i)++;
            while (r[*i] && r[*i] != '"')
                (*i)++;
            if (r[*i] == '"' && (*i)++)
                return (0);
            else
                return (1);
        }
        break ;
    }
    return (0);
}

int    check_pipe(char *r)
{
    int     i;
    int     tmp;

    i = 0;
    while (r[i])
    {
        tmp = 0;
        while (r[i] && (r[i] == ' ' || r[i] == '|'))
        {
            if (r[i] == '|' && ++tmp && tmp >= 2)
                return (1);
            i++;
        }
        while (r[i] && r[i] != ' ' && r[i] != '|'
         && r[i] != '"' && r[i] != '\'')
            i++;
        if (go_next_qoute(r, &i))
            return (1);
    }
    return (0);
}

int    check_syntax(t_data *info, char *rl)
{
    int     check;
    char    *s;
    int     l;

    add_history(rl);
    s = ft_strtrim(rl, " ");
    l = ft_strlen(s) - 1;
    if (s[l] == '|' || s[l] == '>' || s[l] == '<'
       || s[0] == '|')
        return (err_message(info, "Syntax Error"));
    free(s);
    if (check_pipe(rl))
        return (err_message(info, "Syntax Error"));
    return (0);
}
