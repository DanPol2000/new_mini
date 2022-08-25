/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorse <chorse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:15:13 by chorse            #+#    #+#             */
/*   Updated: 2022/06/27 12:39:40 by chorse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void handler(t_args *args)
{
	t_args	*tmp;

	tmp = args;
	while (tmp)
	{
		printf("%s key = %d| \n", tmp->value, tmp->key);
		tmp = tmp->next;
	}
}


void check_first(t_data *data, t_args *args)
{
	t_args *tmp;

	tmp = args;
	if (tmp->value)
	{
		if (!ft_strcmp(tmp->value, "echo"))
			data->flag = 1;
	}
}

// int if_env(t_args *args)
// {
// 	t_args *tmp;
// 	int i = 0;
// 	int y = 0;
// 	char *env;
	
// 	env = malloc(100);
// 	tmp = args;
	
// 	while (tmp)
// 	{
// 		i = 0;
// 		while (i < ft_strlen(tmp->value))
// 		{
// 			if (tmp->value[i] == '$' && tmp->key != 1)
// 			{
// 				i++;
// 				while (tmp->value[i])
// 				{
// 					env[y] = tmp->value[i];
// 					y++;
// 					i++;
// 				}
// 				return env;
// 			}
// 			i++;	
// 		}
// 		tmp = tmp->next;
// 	}
// }