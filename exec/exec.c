/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/08 09:42:08 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void exec(t_data *info)
{
	int	i;
	int	count;
	int  status = 0;
	int wpid;

	info->pipe_count = find_pipe_count(info);
	info->process = malloc(sizeof(t_process) * (info->pipe_count + 1));
	i = -1;
	while (++i < info->pipe_count)
		pipe(info->process[i].fd);
	i = -1;

	count = 0;
	while (++i < info->pipe_count + 1)
	{
		exec_command(info, info->cmd->commands + count, count, i);
		pipe_finder(info, &count);
	}
	i = -1;
	pipe_close(info);
	while (waitpid(-1, NULL, 0) > 0);
}

int	exec_command(t_data *info, char **read_line, int count, int i)
{
	if (!read_line[0])
		return (0);
	create_fork(info, read_line, count, i);
	return (0);
}

void	create_fork(t_data *info, char **read_line, int count, int i)
{
	char	**new_exec;
	pid_t	fork_id;

	fork_id = fork();
	if (fork_id == -1)
		exit(42);
	if (fork_id == 0)
	{
		ft_process_merge(info, i);
		new_exec = redirect(info, count);
		builtin(info, new_exec, count);
		find_path_and_exec(info, new_exec);
		exit(42);
	}
}

void	find_path_and_exec(t_data *info, char **read_line)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	i = -1;
	while (info->paths[++i])
	{
		tmp2 = ft_strjoin(info->paths[i], "/");
		tmp = ft_strjoin(tmp2, read_line[0]);
		free(tmp2);
		if (access(tmp, F_OK) != -1)
		{
			execve(tmp, read_line, info->env_p);
			free(tmp);
			exit(42);
		}
		free(tmp);
	}
}
