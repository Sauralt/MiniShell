/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:20:01 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/10 18:21:33 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_list_tok(t_shell *data, char *str, char quote)
{
	t_token	*temp;

	if (!str)
		return ;
	temp = ft_new_token(data, str);
	if (!temp)
	{
		free_tokens(data->token);
		return ;
	}
	ft_add_token(&data->token, temp);
	if (quote == '\0')
		check_meta_in_word(data, temp);
}

int	meta_char(char *str)
{
	if (ft_strcmp(str, "<") != 0 && ft_strcmp(str, ">") != 0
		&& ft_strcmp(str, ">>") != 0 && ft_strcmp(str, "<<") != 0
		&& ft_strcmp(str, "|") != 0)
		return (1);
	return (0);
}

int	set_token_type(t_shell *data, char *str)
{
	char	*path;
	int		i;

	i = 0;
	if (is_builtin(str) == true)
		return (1);
	path = find_path(str, data->env, i);
	if (path)
	{
		free(path);
		return (1);
	}
	if (meta_char(str) == 0)
		return (2);
	return (0);
}

static void	full_cmd(t_shell *data)
{
	t_token	*t;

	t = data->token;
	while (t->next != data->token)
	{
		if (t->type == 1)
			t = add_param(data, t);
		if (t->next == data->token)
			break ;
		t = t->next;
	}
	t = data->token;
	while (t->next != data->token)
	{
		if (t->type == 2)
		{
			check_meta_char(data, t);
		}
		if (t->next == data->token)
			break ;
		t = t->next;
	}
}

int	init_tokens(t_shell *data, char *line)
{
	int		flag;
	char	*temp;

	temp = remove_closed_quotes(line);
	if (!temp)
		return (1);
	flag = parsing(data, line);
	if (!data->token)
		return (free(temp), 2);
	if (flag == 1)
	{
		free(temp);
		return (1);
	}
	if (flag == 2)
	{
		free(temp);
		return (2);
	}
	free(temp);
	if (check_tok_order(data) == 2)
		return (2);
	full_cmd(data);
	return (last_check(data));
}
