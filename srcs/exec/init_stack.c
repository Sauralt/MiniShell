/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:23:53 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/11 16:22:45 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_cmd(t_shell *data)
{
	t_token	*t;
	t_stack	*s;
	int		i;

	t = data->token;
	s = data->cmd;
	i = 0;
	while (t->next != data->token)
	{
		if (t->type == 1)
		{
			s->id = i;
			s->str = t->str;
			s->next = t->next;
			s->prev = t->prev;
			s = s->next;
		}
		t = t->next;
		i++;
	}
}

static int	init_meta(t_shell *data)
{
	t_token	*t;
	t_stack	*s;
	int		i;

	t = data->token;
	s = data->meta;
	i = 0;
	while (t->next != data->token)
	{
		if (t->type == 1)
		{
			s->id = i;
			s->str = t->str;
			s->next = t->next;
			s->prev = t->prev;
			s = s->next;
		}
		t = t->next;
		i++;
	}
}

static int	init_rand(t_shell *data)
{
	t_token	*t;
	t_stack	*s;
	int		i;

	t = data->token;
	s = data->rand;
	i = 0;
	while (t->next != data->token)
	{
		if (t->type == 1)
		{
			s->id = i;
			s->str = t->str;
			s->next = t->next;
			s->prev = t->prev;
			s = s->next;
		}
		t = t->next;
		i++;
	}
}

int	init_stacks(t_shell *data)
{
	init_cmd(data);
	init_rand(data);
	init_meta(data);
}
