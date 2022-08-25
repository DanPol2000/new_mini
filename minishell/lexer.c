/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorse <chorse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:17:22 by chorse            #+#    #+#             */
/*   Updated: 2022/06/28 14:55:26 by chorse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char  *what_env(t_args *args)
{
	t_args *tmp;
	int i = 0;
	int y = 0;
	char *env;
	
	env = malloc(100);
	tmp = args;
	
	while (tmp)
	{
		i = 0;
		while (i < ft_strlen(tmp->value))
		{
			if (tmp->value[i] == '$' && tmp->key != 1)
			{
				i++;
				while (tmp->value[i])
				{
					env[y] = tmp->value[i];
					y++;
					i++;
				}
				return env;
			}
			i++;	
		}
		tmp = tmp->next;
	}
	env[i] = '\0';
	free_lst(tmp);
	return env;
}

// void	printf_token_list(t_args *token_list)
// {
// 	t_args	*tmp_token;
	
// 	tmp_token = token_list;
// 	printf("\n\n%p\n", token_list);
// 	printf("TOKEN_LIST:\n\n");
// 	while (tmp_token)
// 	{
// 		printf("%s|", tmp_token->value);
// 		tmp_token = tmp_token->next;
// 	}
// }

void lexer(t_data *data, t_args **args)
{
	int smb = 0;
	char *tmp;
	int len = 0;
	

	len = ft_strlen(data->line);
	while (data->line[smb])
	{
		tmp = malloc(sizeof(char) * (len + 1));
		int i = 0;
		int key = 0;
		if (is_space(data->line[smb])) //skip space
		{
			while (is_space(data->line[smb]))
				smb++;
		}
		if (data->line[smb] && !is_space(data->line[smb])) //check general symbols
		{
			if (data->line[smb] != '"' && data->line[smb] != 39)  
			{
							
				while (data->line[smb] && !is_space(data->line[smb]))
				{
					if (ft_strlen(tmp) < 1)
					{
						tmp[i] = data->line[smb];
						i++;
						smb++;
					}
					else
					{
						tmp[i] = data->line[smb];
						smb++;
						i++;
					}
				}
			}
			if (data->line[smb] == 39 && !is_space(data->line[smb])) //check single_quote
			{
				smb++;
				key = 1;
				if (data->line[smb] == '\0')
				{
						write(1, "\33[2K\rLack of second quote\n", 26);
						g_ask = 1;
						break ;
				}
				while (data->line[smb] && data->line[smb] != 39)
				{
					
					if (data->line[smb+1] == '\0')
					{
						write(1, "\33[2K\rLack of second quote\n", 26);
						g_ask = 1;
						break ;
					}
					else
					{
						tmp[i] = data->line[smb];
						smb++;
						i++;
					}
				}
				smb++;
			}
			if (data->line[smb] == '"' && !is_space(data->line[smb])) //check double_quote
			{
				smb++;
				key = 2;
				if (data->line[smb] == '\0')
				{
						write(1, "\33[2K\rLack of second quote\n", 26);
						g_ask = 1;
						break ;
				}
				while (data->line[smb] && data->line[smb] != '"')
				{
					if (data->line[smb+1] == '\0')
					{
						write(1, "\33[2K\rLack of second quote\n", 26);
						g_ask = 1;
						break ;
					}
					else
					{
						tmp[i] = data->line[smb];
						smb++;
						i++;
					}
				}
				smb++;
			}
			if (data->line[smb] == '$' && !is_space(data->line[smb]))
			{
				smb++;
				key = 1;
				if (data->line[smb] == '$')
				{
					int num = getpid();
					printf("PID = %d\n", num);
					char *arg = ft_itoa(num);
					while (arg[i] != '\0')
					{
						tmp[i] = arg[i];
						i++;
					}
				}
				// if (data->line[smb] == '?')
				// {
				// 	printf("PID = %d\n", arg);
				// 	break ; 
				// }
				// key = 2;
				// while (data->line[smb])
				// {
				// 	tmp[i] = data->line[smb];
				// 	smb++;
				// 	i++;
				// }
				smb++;
			}
		}
		tmp[i] = '\0';
		ft_create_lst(tmp, args, key);
		free(tmp);
	}
}


int	check_tokens(t_args *head)
{
	t_args	*args;

	args = head;
	while (args)
	{
		if (is_empty(args->value))
			args->key = EMPTY;
		else if (!ft_strcmp(args->value, "|"))
			args->key = PIPE;
		else if (!ft_strcmp(args->value, ">"))
			args->key = TRUNC;
		else if (!ft_strcmp(args->value, "<"))
			args->key = INPUT;
		else if (!ft_strcmp(args->value, ">>"))
			args->key = APPEND;
		else if (args->prev == NULL || args->prev->key >= TRUNC)
			args->key = CMD;
		else
			args->key = ARG;
		args = args->next;
	}
	return (0);
}

int	is_empty(char *str)
{
	if (!ft_strcmp(str, "\"\""))
		return (1);
	if (!ft_strcmp(str, "''"))
		return (1);
	if (str[0] == '\0')
		return (1);
	return (0);
}