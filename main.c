/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:44:10 by museker           #+#    #+#             */
/*   Updated: 2023/09/19 02:37:37 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_path_and_exec(t_data *info, char **read_line)
{
	int		i;
	pid_t 	fork_id;
	char	*tmp;
	char 	*tmp2;
	char 	**tmp3;

	i = -1;
	fork_id = fork();
	if (!read_line[0])
		return (0);
	if (fork_id == 0)
	{
		while (info->paths[++i])
		{
			tmp2 = ft_strjoin(info->paths[i], "/");
			tmp = ft_strjoin(tmp2, read_line[0]);
			free(tmp2);
			if (access(tmp, F_OK) != -1)
			{
				execve(tmp, read_line, NULL);
				free(tmp);
				exit(0);
			}
			free(tmp);
		}
	}
	return (0);
}

void	set_env_p(t_data *info, char **env_p)
{
	int		i;
	char	**temp;
	t_list	*tmplst_1;
	t_list	*result_lst;

	i = -1;
	while (env_p[++i])
	{
		temp = ft_split(env_p[i], '=');
		tmplst_1 = ft_lstnew(temp[0], temp[1]);
		ft_lstadd_back(&result_lst, tmplst_1);
		free(temp);
	}
	info->env_lst = result_lst;
	info->paths = ft_split(getenv("PATH"), ':');
}

int	main(int argc, char *argv[], char **env_p)
{
	t_data		*info;
	char		**read_line;
	char		*s;

	info = malloc(sizeof(t_data));
	set_env_p(info, env_p);
	while (1)
	{
		s = readline("(Minishell)$> ");
		read_line = ft_split(s, ' ');
		find_path_and_exec(info, read_line);
		free(read_line);
		free(read_line[0]);
		free(s);
	}
	return (0);
}
