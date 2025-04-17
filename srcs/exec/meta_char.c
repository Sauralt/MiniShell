/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:15:33 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/17 17:04:40 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	infile_redirect(t_shell *data, t_token *t)
{
	int	infile;

	infile = open(t->next->str[0], O_RDONLY, 0644);
	if (infile == -1)
	{
		ft_dprintf(2, "%s, no file or directory or not permitted\n",
			t->prev->str[0]);
		return ;
	}
	if (t != data->token)
	{
		t->prev->infile = infile;
		t->next->type = 2;
	}
	else
	{
		t->next->next->infile = infile;
		t->next->type = 2;
	}
}

static void	outfile_trunc(t_token *t)
{
	int	outfile;

	outfile = open(t->next->str[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		ft_dprintf(2, "%s, no file or directory or not permitted\n",
			t->prev->str[0]);
		return ;
	}
	t->prev->outfile = outfile;
	t->next->type = 2;
}

static void	outfile_append(t_token *t)
{
	int	outfile;

	outfile = open(t->next->str[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
	{
		ft_dprintf(2, "%s, no file or directory or not permitted\n",
			t->prev->str[0]);
		return ;
	}
	t->prev->outfile = outfile;
	t->next->type = 2;
}

void	check_meta_char(t_shell *data, int i)
{
	t_token	*t;
	int		j;

	j = 0;
	t = data->token;
	while (j < i - data->del_num)
	{
		t = t->next;
		j++;
	}
	if (strcmp(t->str[0], "<") == 0)
		infile_redirect(data, t);
	if (strcmp(t->str[0], ">") == 0)
		outfile_trunc(t);
	if (strcmp(t->str[0], ">>") == 0)
		outfile_append(t);
	if (strcmp(t->str[0], "<<") == 0)
		heredoc(data, t->next->str[0]);
}
