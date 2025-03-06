/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:20:01 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/06 16:21:40 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_list_tok(t_shell *data, char **str)
{
	int	i;

	data->token->token = str[i];
	i = 1;
	while (str[i])
	{
		
	}
}

void	set_token_type(t_shell *data, char *line, int type)
{
	t_token	*t;

	t = data->token;
	if (type = 2)
	{
		while (t->token->next != data->token)
			t = t->next;
	}
}

int	init_tokens(t_shell *data, char *line)
{
	int		i;
	char	**str;
	char	*path;

	i = 0;
	str = ft_split(line, ' ');
	if (!str)
		return (1);
	init_list_tok(data);
	while (str[i])
	{
		path = (find_path(str[i]))
		if (!path)
			set_token_type(data, line, 2);
		else
			set_token_type(data, line, 1);
	}
}
