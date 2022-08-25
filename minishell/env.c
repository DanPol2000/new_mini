/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorse <chorse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:16:01 by chorse            #+#    #+#             */
/*   Updated: 2022/06/24 13:55:24 by chorse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void env_check(t_data *data, char **env)
{
	int d = 0;
	int i = -1;
	int t = 0;
	t_env *env_list;
	t_env *new_lst;
	char *value;
	char *key;
	env_list = malloc(sizeof(t_env));
	data->env_save = env_list;
	while (env[t])
	{
		d = 0; 
		i = 0;
		new_lst = malloc(sizeof(t_env));
		while (env[t][d] != '=')
			d++;
		key = malloc(sizeof(char) * d);
		d = 0;
		while (env[t][d] != '=')
			key[i++] = env[t][d++];
		key[i] = '\0';
		new_lst->key = key;
		value = malloc(sizeof(char) * (ft_strlen(env[t]) - d) + 1);
		i = 0;
		while (env[t][d])
			value[i++] = env[t][++d];
		value[i] = '\0';
		new_lst->value = value;
		new_lst->next = NULL;
		env_list->next = new_lst;
		env_list = new_lst;
		t++;
	}
}
