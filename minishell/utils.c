/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorse <chorse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:14:30 by chorse            #+#    #+#             */
/*   Updated: 2022/06/27 13:04:45 by chorse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_lstsize(t_args *lst)
{
	t_args	*s;
	int		i;

	i = 0;
	s = lst;
	while (s)
	{
		i++;
		s = s->next;
	}
	return (i);
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

	if (*lst != NULL)
	{
		tmp = *lst;
		tmp = ft_lstlast(*lst);
		tmp->next = new;
		new->prev = tmp;
		return ;
	}
	*lst = new;

}

void ft_create_lst(char *tmp, t_args **args, int key)
{
	t_args	*new;
	char *new_str;

	new_str = ft_strdup(tmp);
	new = ft_lstnew(new_str, key);
	if (!*args)
	{
		*args = new;
		return ;
	}
	else
		ft_lstadd_back(args, new);
}

int is_space(char c)
{
	if (c == ' ' || c == '	' || c == '\t' || \
		c == '\n' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

void free_lst(t_args *args)
{
	t_args	*head;
	t_args	*tmp;

	head = args;
	while (head)
	{
		tmp = head;
		head = head ->next;
		free(tmp);
	}
	free(args);
}