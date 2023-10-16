/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:23 by museker           #+#    #+#             */
/*   Updated: 2023/09/26 21:13:36 by mucakmak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	create_fork_and_exec(t_data *info, char **read_line)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	pid_t	fork_id;

	i = -1;
	if (!read_line[0])
		return (0);
	fork_id = fork();
	if (fork_id == 0)
	{
		find_path_and_exec(info, read_line);
		printf("minishell: %s: command not found\n", read_line[0]);
		exit(42);
	}
	else if (fork_id > 0)
		wait(&fork_id);
	return (0);
}

void	set_env_p(t_data *info, char **env_p)
{
	int		i;
	char	**temp;
	t_list	*tmplst_1;

	i = -1;
	info->env_lst = NULL;
	while (env_p[++i])
	{
		temp = ft_split(env_p[i], '=');
		tmplst_1 = ft_lstnew(temp[0], temp[1]);
		ft_lstadd_back(&(info->env_lst), tmplst_1);
		free(temp);
	}
	info->env_p = env_p;
	info->paths = ft_split(getenv("PATH"), ':');
}

int	main(int argc, char *argv[], char **env_p)
{
	t_data		*info;
	char		*read_line;

	info = malloc(sizeof(t_data));
	info->cmd = malloc(sizeof(t_commands));
	set_env_p(info, env_p);
	while (1)
	{
		read_line = readline("\033[0;31m(Minishell)$>\033[0m ");
		add_history(read_line);
		lexer(info, read_line);
		create_fork_and_exec(info, info->cmd->commands);
		// system("leaks minishell");
	}
	return (0);
}

// char	**ft_cakma_split(char const *s, char c)
// {
// 	int		i;
// 	int		j;
// 	int		temp;
// 	char	**str;
// 	int		abc;
// 	i = 0;
// 	j = 0;
// 	str = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
// 	if (!str)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		abc = i;
// 		while (s[i] && s[i] == c)
// 			i++;
// 		while (s[i] && s[i] != c)
// 			i++;
// 		if (count_word(s, c) == j)
// 			break ;
// 		str[j++] = ft_substr(s, abc, i - abc);
// 		abc = i;
// 	}
// 	str[j] = 0;
// 	return (str);
// }


// int main()
// {
// 	int i = -1;
// 	char **split;
// 	split = pipe_split("echo abd|cd", '|');
// 	while (split[++i])
// 		printf("(%s)\n", split[i]);
// }