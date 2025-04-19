/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:20:01 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/18 12:53:37 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_list_tok(t_shell *data, char *str, int flag)
{
	t_token	*temp;

	if (!str)
		return ;
	temp = ft_new_token(data, str, flag);
	if (!temp)
	{
		free_tokens(data->token);
		return ;
	}
	ft_add_token(&data->token, temp);
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

int	set_token_type(t_shell *data, char *str)
{
	char	*path;

	if (is_builtin(str) == true)
		return (1);
	path = find_path(str, data->env);
	if (path)
	{
		free(path);
		return (1);
	}
	if (meta_char(str) == 1)
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
		else if (t->type == 2)
			check_meta_char(data, t);
		t = t->next;
	}
	if (t->type == 1)
		t = add_param(data, t);
	else if (t->type == 2)
		check_meta_char(data, t);
}

int	init_tokens(t_shell *data, char *line)
{
	if (parsing(data, line) == 1)
		return (1);
	full_cmd(data);
	return (0);
}
