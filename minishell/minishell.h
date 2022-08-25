/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorse <chorse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:59:05 by chorse            #+#    #+#             */
/*   Updated: 2022/06/28 15:51:28 by chorse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

extern int g_ask;

typedef struct s_args
{
	char			*value;
	struct s_args	*next;
	int				key;
	struct s_args	*prev;
}	t_args;

typedef struct s_data
{
	char	*line;
	int		flag;
	t_args	*args;
}	t_data;

void	rl_replace_line(const char *text, int clear_undo);
void	check_first();
void	env_check(t_data *data, char **env);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
void	lexer(t_data *data, t_args **args);
int		is_space(char c);
void	ft_create_lst(char *tmp, t_args **args, int key);
void	ft_lstadd_back(t_args **lst, t_args *new);
t_args	*ft_lstlast(t_args *lst);
t_args	*ft_lstnew(void *value, int key);
int		ft_lstsize(t_args *lst);
void	handler(t_args *args);
void	parser(t_data *data, t_args *args);
void	ft_lstadd_front(t_args **lst, t_args *new);
void	printf_token_list(t_args *token_list);
char	*what_env(t_args *args);
char	*ft_strdup(char *s1);
int		ft_strcmp(char *s1, char *s2);
int		check_tokens(t_args *head);
int		is_empty(char *str);
void	free_lst(t_args *args);
void	func_ex(int sig);
void	cmd_lst_create(t_data *data, t_args *args);
char	*ft_itoa(int number);

#endif