/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorse <chorse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:28:06 by chorse            #+#    #+#             */
/*   Updated: 2022/06/28 16:07:58 by chorse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void add_env(t_args *args);

int g_ask;
int	g_exit_status;

void signal_h(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}


int main()
{
	t_data *data;
	t_args *args;

	data = malloc(sizeof(t_data));
	args = NULL;
	data->flag = 0;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, signal_h);
		data->line = readline("\e[1;32mbash$ \e[0;37m");
		if (data->line == NULL)
		{
			write(1, "\33[2K\rminishell$ exit\n", 22);
			exit(0);
		}
		if (data->line && data->line[0] != '\0')
		{	
			add_history(data->line);
			parser(data, args);
		}
		signal(SIGINT, SIG_IGN);
		free(data->line);
		data->line = NULL;
		free_lst(args);
	}
	return (0);
}


void parser(t_data *data, t_args *args)
{
	// char *s;
	// char *env;
	// int key;
	
	lex er(data, &args);
	// add_env(args);
	// env = NULL;
	// printf_token_list(args);
	// check_first(data, args);
	// s = what_env(args);
	// if (s[0] == '?')
	// {	printf("%d\n", g_ask);
	// 	return ;
	// }
	// if (g_ask == 1)
	// 	return ;
	// g_ask = 0;
	// if (s != NULL) 
	// {	
	// 	env = getenv(s);
	// 	key = 0;
	// 	ft_create_lst(env, args, key);
	// }
	// g_ask = 0;
	check_tokens(args);
	// handler(args);
}

void add_env(t_args *args)
{
	t_args *tmp;

	tmp = args;
	while (tmp != NULL)
	{
		printf("TMP = %s\n", tmp->value);
		tmp = tmp->next;
	}
	free_lst(tmp);
	// ft_create_lst(tmp, args, key);
}