/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorse <chorse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:15:12 by chorse            #+#    #+#             */
/*   Updated: 2022/06/24 17:06:51 by chorse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_args
{
	int				key;
	char			*value;
	struct s_args	*next;
	struct s_args	*prev;
}	t_args;

typedef struct s_data
{
	char	*line;
	t_args	*args;
	t_env	*env_save;
}	t_data;



int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

void	printf_token_list(t_args *token_list)
{
	t_args	*tmp_token;
	
	tmp_token = token_list;
	printf("\n\n%p\n", token_list);
	printf("TOKEN_LIST:\n\n");
	while (tmp_token != NULL)
	{
		printf("%s|", tmp_token->value);
		tmp_token = tmp_token->next;
	}
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	size_t	i;

	i = 0;
	s2 = malloc((ft_strlen(s1) + 1) * (sizeof(char)));
	if (!s2)
		return (NULL);
	else
	{
		while (s1[i] != '\0')
		{
			s2[i] = s1[i];
			i++;
		}
	}
	s2[i] = '\0';
	return (s2);
}

t_args	*ft_lstlast(t_args *lst)
{
	t_args	*tmp;

	tmp = lst;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}


t_args	*ft_lstnew(void *value, int key)
{
	t_args	*new;

	new = malloc(sizeof(t_args));
	if (new)
	{
		new->value = value;
		new->key = key;
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

void	ft_lstadd_back(t_args **lst, t_args *new)
{
	t_args	*tmp;

	if (*lst != NULL && lst != NULL)
	{
		tmp = *lst;
		tmp = ft_lstlast(*lst);
		tmp->next = new;
		new->prev = tmp;
		return ;
	}
	*lst = new;

}

void ft_create_lst(char *tmp, t_args **args)
{
	t_args	*new;
	char *new_str;

	new_str = ft_strdup(tmp);
	new = ft_lstnew(new_str, -1);
	if (!*args)
	{
		*args = new;
		printf("Ee = %s\n", (*args)->value);
		return ;
	}
	else
		ft_lstadd_back(args, new);
}


int main()
{
	t_data *data;
	data = malloc(sizeof(t_data));
	t_args *args;
	char *line_s = "Eefe";
	char *line_d = "ava";
	ft_create_lst(line_d, &args);
	printf("Ee = %s\n", args->value);
	ft_create_lst(line_s, &args);
	printf_token_list(args);
    return 0;
}