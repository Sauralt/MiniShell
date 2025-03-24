/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:34:34 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/24 15:25:56 by mgarsaul         ###   ########.fr       */
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
		free(*s);
		*s = NULL;
		return ;
	}
	p = (*s)->prev;
	p->next = (*s)->next;
	(*s)->next->prev = p;
	t = *s;
	*s = (*s)->next;
	free(t);
}

void	add_param(t_shell *data, int i, char **str)
{
	t_token	*t;
	t_token	*u;
	int		j;
	int		count;

	j = -1;
	t = data->token;
	while (j++ < i - 1)
		t = t->next;
	u = t;
	count = 1;
	while (u->next->type == 4)
	{
		count++;
		u = u->next;
	}
	free_str(t->str);
	t->str = malloc(sizeof(char) * (count + 1));
	j = 0;
	while (j < count)
		t->str[j++] = ft_strdup(str[i++]);
	t->str[j] = NULL;
}
