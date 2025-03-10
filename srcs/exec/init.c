/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:20:01 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/10 16:33:56 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	correct_type(t_shell *data)
{
	t_token	*t;

	if (!data->token)
		return (1);
	t = data->token;
	while (t && t->next && t->next != data->token)
	{
		if (t->type == 0)
			return (1);
		t = t->next;
	}
	if (t->type == 0)
		return (1);
	return (0);
}

static void	init_list_tok(t_shell *data, char **str)
{
	int	i;

	if (!str)
		return ;
	data->token = ft_new_token(str[0]);
	i = 1;
	while (str[i])
	{
		ft_add_token(&data->token, ft_new_token(str[i]));
		i++;
	}
}

static int	meta_char(char *str)
{
	if (ft_strncmp(str, "<", 1) == 1 || ft_strncmp(str, ">", 1) == 1
		|| ft_strncmp(str, ">>", 2) == 1 || ft_strncmp(str, "<<", 2) == 1
		|| ft_strncmp(str, "|", 1) == 1 || ft_strncmp(str, "$", 2) == 1
		|| ft_strncmp(str, "$?", 2) == 1)
		return (1);
	return (0);
}

static void	set_token_type(t_shell *data, int type)
{
	t_token	*t;

	t = data->token;
	if (type == 2)
	{
		while (t && t->next && t->next != data->token)
		{
			if (meta_char(t->str) == 1)
				t->type = 0;
			else
				t->type = 2;
			t = t->next;
		}
		t->type = 2;
	}
	else
	{
		while (t && t->next && t->next != data->token)
		{
			t->type = 1;
			t = t->next;
		}
		t->type = 1;
	}
}

int	init_tokens(t_shell *data, char *line)
{
	int		i;
	int		j;
	char	**str;
	char	*path;

	i = 0;
	j = 0;
	str = ft_split(line, ' ');
	if (!str)
		return (1);
	init_list_tok(data, str);
	while (str[i])
	{
		path = find_path(str[i], data->env, j);
		if (!path)
			set_token_type(data, 2);
		else
			set_token_type(data, 1);
		i++;
	}
	if (correct_type(data) == 1)
		return (1);
	return (0);
}
