/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:43:11 by museker           #+#    #+#             */
/*   Updated: 2023/09/28 02:41:32 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}	t_list;

typedef struct s_commands
{
	char			**commands;
	int				fd[2];
}	t_commands;

typedef struct s_data
{
	char			**paths;
	char			**env_p;
	t_list			*env_lst;
	t_list			*arg;
}	t_data;

// main.c
void		find_path_and_exec(t_data *info, char **read_line);
int			create_fork_and_exec(t_data *info, char **read_line);
void		set_env_p(t_data *info, char **env_p);

// utils/lst_all.c
t_list		*ft_lstnew(void *key, void *value);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);

// utils/ft_split.c
char		*ft_strchr(const char *s, int c);
int			count_word(const char *p, char c);
char		**ft_split(char const *s, char c);

// utils/ft_str_1.c
size_t		ft_strlen(const char *str);
int			ft_find_index(char *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_before_c(char *s, char c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);

// utils/ft_str_2.c
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
int			find_key(t_data *info, char *s);
// lexer/lexer_str.c
char		*check_dollar(t_data *info, char *s);
void		*dollar_split(t_data *info, char *s, int *in);
void		*no_dollar_split(char *s, int *in);
char		*replace_dollar(t_data *info, char *s);
char		*char_combining(char **s);

// lexer/lexer_utils.c
int			pipe_ct(char *read_line);
char		*add_space(char *rd);
int			ft_char_count(char *read_line, int c);
void		two_pointer_free(char **s);
char		*lst_combining(t_data *info);

// lexer/lexer.c
char		**lexer(t_data *info, char *read_line);
void		quote(t_data *info, char *read_line);
void		quotes(t_data *info, char *read_line, int *index, int c1);
void		no_quote(t_data *info, char *read_line, int *index);

#endif