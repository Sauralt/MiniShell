/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:15:33 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/06 14:35:33 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	infile_redirect(t_shell *data, t_token *t)
{
	int		infile;

	infile = open(t->next->str[0], O_RDONLY, 0644);
	if (infile == -1)
	{
		ft_dprintf(2, "%s, no file or directory or not permitted\n",
			t->next->str[0]);
		data->exit_code = 1;
		t->next->type = 3;
		return ;
	}
	if (t != data->token)
		t->prev->infile = infile;
	else
		t->next->next->infile = infile;
	data->exit_code = 0;
	t->next->type = 3;
}

static void	outfile_trunc(t_shell *data, t_token *t)
{
	int		outfile;
	t_token	*temp;

	outfile = open(t->next->str[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		ft_dprintf(2, "%s, no directory or not permitted\n",
			t->next->str[0]);
		data->exit_code = 1;
		t->next->type = 3;
		return ;
	}
	temp = t;
	while (temp->type != 1 && temp->prev != t)
		temp = temp->prev;
	temp->outfile = outfile;
	data->exit_code = 0;
	t->next->type = 3;
}

static void	outfile_append(t_shell *data, t_token *t)
{
	int		outfile;
	t_token	*temp;

	outfile = open(t->next->str[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
	{
		ft_dprintf(2, "%s, no directory or not permitted\n",
			t->next->str[0]);
		data->exit_code = 1;
		t->next->type = 3;
		return ;
	}
	temp = t;
	while (temp->type != 1 && temp->prev != t)
		temp = temp->prev;
	temp->outfile = outfile;
	data->exit_code = 0;
	t->next->type = 3;
}

void	check_meta_char(t_shell *data, t_token *t)
{
	if (t->next == t || t->next == data->token)
		return ;
	if (strcmp(t->str[0], "<") == 0)
		infile_redirect(data, t);
	if (strcmp(t->str[0], ">") == 0)
		outfile_trunc(data, t);
	if (strcmp(t->str[0], ">>") == 0)
		outfile_append(data, t);
	if (strcmp(t->str[0], "<<") == 0)
		heredoc(data, t, t->next->str[0]);
}
