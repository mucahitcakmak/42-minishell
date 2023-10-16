/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/04 18:40:25 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		tmp3 = ft_strtrim(tmp, " ");
		free(tmp2);
		if (access(tmp3, F_OK) != -1)
		{
			execve(tmp3, read_line, info->env_p);
			free(tmp);
			exit(42);
		}
		free(tmp);
	}
}

char	**read_line_edit(t_data *info, int index)
{
	int		i;
	int		temp;
	char	**s;
	char	*tmp;

	temp = index;
	while (info->cmd->commands[++index])
		if (ft_strchr(info->cmd->commands[index], '|')
			&& info->cmd->flags[index] == Q0)
			break ;
	s = (char **)malloc(sizeof(char *) * (index - temp + 1));
	i = 0;
	while (info->cmd->commands[temp] && temp < index)
	{
		if (info->cmd->flags[temp] == Q0)
		{
			tmp = info->cmd->commands[temp++];
			if (tmp[0])
				s[i++] = ft_strtrim(tmp, " ");
			else
				s[i++] = tmp;
		}
		else
			s[i++] = info->cmd->commands[temp++];
	}
	s[i] = NULL;
	return (s);
}

void	pipe_close(t_data *info)
{
	int	i;
	
	i = 0;
	while (i < info->pipe_count)
	{
		close(info->process[i].fd[0]);
		close(info->process[i].fd[1]);
		i++;
	}
}

void	ft_process_merge(t_data *info, int i)
{
	if (i == 0)
		dup2(info->process[0].fd[1], 1);
	else if (i == info->pipe_count)
		dup2(info->process[i - 1].fd[0], 0);
	else
	{
		dup2(info->process[i - 1].fd[0], 0);
		dup2(info->process[i].fd[1], 1);
	}
	pipe_close(info);
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
		new_exec = read_line_edit(info, count);
		ft_process_merge(info, i);
		find_path_and_exec(info, new_exec);
		printf("minishell: %s: command not found\n", read_line[0]);
		exit(42);
	}
}

int	exec_command(t_data *info, char **read_line, int count, int i)
{
	if (!read_line[0])
		return (0);
	create_fork(info, read_line, count, i);
	return (0);
}

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

int	find_pipe_count(t_data *info)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (info->cmd->commands[++i])
		if (ft_strchr(info->cmd->commands[i], '|') && info->cmd->flags[i] == Q0)
			count++;
	return (count);
}

void	pipe_finder(t_data *info, int *count)
{
	while (info->cmd->commands[++(*count)])
		if (ft_strchr(info->cmd->commands[*count], '|')
			&& info->cmd->flags[*count] == Q0 && ++(*count))
			break ;
	if (info->cmd->commands[*count]
		&& info->cmd->commands[*count][0] == ' '
		&& info->cmd->flags[*count] == Q0)
	{
		++(*count);
	}
}
