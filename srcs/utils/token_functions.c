/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:34:34 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/18 12:42:01 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(t_shell *data, char *content, int flag)
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
	c->str[0] = ft_strdup(init_nstr(data, content, flag));
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
	if (t->prev)
		t->prev->next = t->next;
	if (t->next)
		t->next->prev = t->prev;
	data->del_num++;
	free_str(t->str);
	free(t);
}


t_token	*add_param(t_shell *data, t_token *t)
{
	t_token	*temp;
	t_token	*temp2;
	char	*str;
	int		len;
	int		i;

	if (!t || !t->next || t->next == t)
		return (t);
	temp = t->next;
	len = 1;
	while (temp->type != 2 && temp != t)
	{
		len++;
		temp = temp->next;
	}
	temp = t->next;
	str = ft_strdup(t->str[0]);
	free_str(t->str);
	t->str = malloc(sizeof(char *) * (len + 2));
	if (!t->str)
		return (t);
	t->str[0] = str;
	len--;
	i = 1;
	while (len > 0)
	{
		temp2 = temp->next;
		t->str[i] = ft_strdup(temp->str[0]);
		delone(data, temp);
		temp = temp2;
		i++;
		len--;
	}
	t->str[i] = NULL;
	return (t);
}
