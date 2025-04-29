/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:34:34 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/29 15:57:46 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(t_shell *data, char *content)
{
	t_token	*c;

	c = malloc(sizeof(*c));
	if (c == NULL)
		return (NULL);
	c->str = malloc(sizeof(char *) * 2);
	if (!c->str)
	{
		free(c);
		return (NULL);
	}
	c->str[0] = ft_strdup(content);
	if (!c->str[0])
	{
		free_str(c->str);
		free(c);
		return (NULL);
	}
	c->type = set_token_type(data, content);
	c->str[1] = NULL;
	c->infile = 0;
	c->outfile = 1;
	c->next = c;
	c->prev = c;
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

void	delone(t_shell *data, t_token *t)
{
	if (!t)
		return ;
	if (t->next == t && t->prev == t)
		data->token = NULL;
	else if (data->token == t)
		data->token = t->next;
	if (t->prev)
		t->prev->next = t->next;
	if (t->next)
		t->next->prev = t->prev;
	data->del_num++;
	free_str(t->str);
	free(t);
	t = NULL;
}

t_token	*add_param(t_shell *data, t_token *t)
{
	t_token	*temp;
	char	*str;
	int		len;

	if (!t || !t->next || t->next == t)
		return (t);
	temp = t->next;
	len = 1;
	while (temp->type != 2 && temp != t && temp != data->token)
	{
		len++;
		temp = temp->next;
	}
	str = ft_strdup(t->str[0]);
	free_str(t->str);
	t->str = malloc(sizeof(char *) * (len + 2));
	if (!t->str)
		return (t);
	change_tok_str(t, str, len, data);
	return (t);
}
