/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:06:28 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/22 20:06:01 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_exec(t_shell *data, t_token *t, int *fd, int *original)
{
	if (t->type == 0)
	{
		ft_dprintf(2, "%s: command not found\n", t->str[0]);
		data->exit_code = 127;
		return ;
	}
	if (t->type == 1)
	{
		ft_pipe(fd, original, data, t);
	}
}

static int	last_token(t_shell *data)
{
	data->exit_code = 2;
	return (ft_dprintf(2, " syntax error near unexpected token `newline'\n")
		, 2);
}

int	check_tok_order(t_shell *data)
{
	t_token	*t;

	t = data->token;
	if (t->str[0][0] == '|')
	{
		data->exit_code = 2;
		return (ft_dprintf(2, " syntax error near unexpected token `%s'\n",
				t->str[0]), 2);
	}
	while (t->next != data->token)
	{
		if (t->type == 2 && t->next->type == 2
			&& ft_strcmp(t->next->str[0], "<<") != 0)
		{
			data->exit_code = 2;
			return (ft_dprintf(2, " syntax error near unexpected token `%s'\n",
					t->next->str[0]), 2);
		}
		t = t->next;
	}
	if (t->type == 2)
		return (last_token(data));
	return (0);
}

char	*find_absolute(char *cmd)
{
	int		i;
	int		j;
	int		len;
	char	*ncmd;

	len = ft_strlen(cmd);
	i = len;
	while (cmd[i] != '/' && i != 0)
		i--;
	if (i == 0)
		return (cmd);
	i++;
	ncmd = malloc(sizeof(char) * (len - i + 1));
	if (!ncmd)
		return (cmd);
	j = 0;
	while (cmd[i])
	{
		ncmd[j] = cmd[i];
		i++;
		j++;
	}
	ncmd[j] = '\0';
	free(cmd);
	return (ncmd);
}

int	last_init(t_token *c, t_shell *data, char *content)
{
	if (!c->str[0])
	{
		free_str(c->str);
		free(c);
		return (1);
	}
	c->type = set_token_type(data, content);
	c->str[1] = NULL;
	c->infile = 0;
	c->outfile = 1;
	c->exit_code = 0;
	c->next = c;
	c->prev = c;
	return (0);
}
