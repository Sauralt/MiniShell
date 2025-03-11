/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:23:53 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/11 17:20:26 by cfleuret         ###   ########.fr       */
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
			if (s == NULL)
			{
				s = ft_new_stack(t);
				s->id = i;
			}
			else
				ft_add_stack(&s, ft_new_stack(t));
		}
		t = t->next;
		i++;
	}
	if (t->type == 1)
	{
		if (s == NULL)
		{
			s = ft_new_stack(t);
			s->id = i;
		}
		else
			ft_add_stack(&s, ft_new_stack(t));
	}
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
		{
			if (s == NULL)
			{
				s = ft_new_stack(t);
				s->id = i;
			}
			else
				ft_add_stack(&s, ft_new_stack(t));
		}
		t = t->next;
		i++;
	}
	if (t->type == 2)
	{
		if (s == NULL)
		{
			s = ft_new_stack(t);
			s->id = i;
		}
		else
			ft_add_stack(&s, ft_new_stack(t));
	}
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
		{
			if (s == NULL)
			{
				s = ft_new_stack(t);
				s->id = i;
			}
			else
				ft_add_stack(&s, ft_new_stack(t));
		}
		t = t->next;
		i++;
	}
	if (t->type == 0)
	{
		if (s == NULL)
		{
			s = ft_new_stack(t);
			s->id = i;
		}
		else
			ft_add_stack(&s, ft_new_stack(t));
	}
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
