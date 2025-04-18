/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:20:01 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/18 14:16:02 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_list_tok(t_shell *data, char **str)
{
	int		i;
	t_token	*temp;

	if (!str)
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		temp = ft_new_token(str[i]);
		if (!temp)
		{
			free_tokens(data->token);
			return ;
		}
		ft_add_token(&data->token, temp);
		i++;
	}
}

static int	meta_char(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (strcmp(str, "<") != 0 && strcmp(str, ">") != 0
		&& ft_strncmp(str, ">>", len) != 0 && strcmp(str, "<<") != 0
		&& strcmp(str, "|") != 0)
		return (1);
	return (0);
}

static void	set_token_type(t_shell *data, int type)
{
	t_token	*t;

	t = data->token;
	while (t->type != -1)
		t = t->next;
	if (type == 2)
	{
		if (meta_char(t->str[0]) == 1)
			t->type = 0;
		else
			t->type = 2;
	}
	else
		t->type = 1;
}

static void	full_cmd(t_shell *data, char **str, int i)
{
	t_token	*t;
	t_token	*temp;

	t = data->token;
	i = 0;
	while (str[i] != NULL)
	{
		temp = t->next;
		if (t->next != t)
		{
			if ((t->type == 1 && t->prev->type != 1)
				|| (t->type == 1 && t == data->token))
				t = add_param(data, i, str);
			else if (t->type == 2)
				check_meta_char(data, i);
			else if (t->prev->type != 2 && t != data->token)
			{
				temp = t->next;
				delone(data, t);
			}
		}
		t = temp;
		i++;
	}
}

int	init_tokens(t_shell *data, char *line)
{
	int		i;
	char	**str;
	char	*path;

	i = 0;
	str = init_str(data, line);
	if (!str)
		return (1);
	init_list_tok(data, str);
	if (!data->token)
		return (1);
	while (str[i] != NULL)
	{
		path = find_path(str[i], data->env);
		if (is_builtin(str[i]) == true)
			set_token_type(data, 1);
		else if (!path)
			set_token_type(data, 2);
		else
			set_token_type(data, 1);
		free(path);
		i++;
	}
	full_cmd(data, str, i);
	free_str(str);
	return (0);
}
