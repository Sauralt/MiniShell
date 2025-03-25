/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:34:34 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/25 16:51:23 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(char *content)
{
	t_token	*c;

	c = malloc(sizeof(*c));
	if (c == NULL)
		return (NULL);
	c->str = malloc(sizeof(char *) * 2);
	if (!c->str)
		return (NULL);
	c->str[0] = ft_strdup(content);
	if (!c->str[0])
	{
		free(c->str);
		return (NULL);
	}
	c->str[1] = NULL;
	c->next = c;
	c->prev = c;
	c->type = -1;
	return (c);
}

void	ft_add_token(t_token **s, t_token *new)
{
	t_token	*p;

	if (new == NULL || s == NULL)
		return ;
	if (*s == NULL)
	{
		*s = new;
		new->next = new;
		new->prev = new;
		return ;
	}
	p = (*s)->prev;
	new->next = *s;
	new->prev = p;
	p->next = new;
	(*s)->prev = new;
}

void	delfirst(t_token **s)
{
	t_token	*p;
	t_token	*t;

	if (!s || !*s)
		return ;
	if ((*s)->next == *s)
	{
		free_str((*s)->str);
		free(*s);
		*s = NULL;
		return ;
	}
	p = (*s)->prev;
	p->next = (*s)->next;
	(*s)->next->prev = p;
	t = *s;
	*s = (*s)->next;
	free_str(t->str);
	free(t);
}

void	delone(t_shell *data, char *str)
{
	t_token	*t;

	t = data->token;
	if (!data || !data->token || !t)
		return ;
	while (strcmp(t->str[0], str) != 0)
	{
		t = t->next;
		if (t == data->token)
			return ;
	}
	t->prev->next = t->next;
	t->next->prev = t->prev;
	free_str(t->str);
	free(t);
}

t_token	*add_param(t_shell *data, int i, char **str)
{
	t_token	*t;
	t_token	*u;
	int		j;
	int		count;

	j = 0;
	t = data->token;
	while (j < i)
	{
		t = t->next;
		j++;
	}
	u = t;
	count = 1;
	while (u != data->token->prev && u->next->type != 2)
	{
		count++;
		u = u->next;
	}
	free_str(t->str);
	t->str = malloc(sizeof(char *) * (count + 1));
	j = 0;
	while (j < count)
	{
		t->str[j] = ft_strdup(str[i]);
		i++;
		j++;
	}
	t->str[j] = NULL;
	// i = 0;
	// while (str[i])
	// {
	// 	printf("%s\n", t->str[i]);
	// 	i++;
	// }
	return (t);
}
