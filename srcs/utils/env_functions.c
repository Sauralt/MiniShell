/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:25:22 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/30 15:56:25 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_new_stack(char *t)
{
	t_env	*c;

	c = malloc(sizeof(*c));
	if (c == NULL)
		return (NULL);
	c->str = ft_strdup(t);
	c->next = c;
	c->prev = c;
	return (c);
}

void	ft_add_stack(t_env **s, t_env *new)
{
	t_env	*p;

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

void	delfirst_stack(t_env **s)
{
	t_env	*p;
	t_env	*t;

	if (!s || !*s)
		return ;
	if ((*s)->next == *s)
	{
		free((*s)->str);
		free(*s);
		*s = NULL;
		return ;
	}
	p = (*s)->prev;
	p->next = (*s)->next;
	(*s)->next->prev = p;
	t = *s;
	*s = (*s)->next;
	free(t->str);
	free(t);
}

void	free_env(t_env *env)
{
	while (env)
	{
		delfirst_stack(&env);
	}
}
