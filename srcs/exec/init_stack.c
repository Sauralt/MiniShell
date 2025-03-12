/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:23:53 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/12 15:17:16 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_stack	*make_stack(t_stack *s, t_token *t, int i)
{
	if (s == NULL)
	{
		s = ft_new_stack(t);
		s->id = i;
	}
	else
		ft_add_stack(&s, ft_new_stack(t), i);
	return (s);
}

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
			s = make_stack(s, t, i);
		t = t->next;
		i++;
	}
	if (t->type == 1)
		s = make_stack(s, t, i);
	data->cmd = s;
	return (0);
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
		if (t->type == 2)
			s = make_stack(s, t, i);
		t = t->next;
		i++;
	}
	if (t->type == 2)
		s = make_stack(s, t, i);
	data->meta = s;
	return (0);
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
		if (t->type == 0)
			s = make_stack(s, t, i);
		t = t->next;
		i++;
	}
	if (t->type == 0)
		s = make_stack(s, t, i);
	data->rand = s;
	return (0);
}

int	init_stacks(t_shell *data)
{
	init_cmd(data);
	init_rand(data);
	init_meta(data);
	return (0);
}
