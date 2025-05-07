/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:15:33 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/06 18:22:19 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	infile_loop(t_token *t, int flag, int infile, int exit_code)
{
	t_token	*temp;

	temp = t;
	if (flag == 0)
	{
		while (temp->type != 1 && temp->prev != t)
			temp = temp->prev;
	}
	else
	{
		while (temp->type != 1 && temp->next != t)
			temp = temp->next;
	}
	temp->infile = infile;
	temp->exit_code = exit_code;
}

static void	infile_redirect(t_shell *data, t_token *t)
{
	int		infile;

	infile = open(t->next->str[0], O_RDONLY, 0644);
	if (infile == -1)
	{
		ft_dprintf(2, "%s, no file or directory or not permitted\n",
			t->next->str[0]);
		if (t != data->token)
			infile_loop(t, 0, 0, 1);
		else
			infile_loop(t, 1, 0, 1);
		t->next->type = 3;
		return ;
	}
	if (t != data->token)
		infile_loop(t, 0, infile, 0);
	else
		infile_loop(t, 1, infile, 0);
	t->next->type = 3;
}

static void	outfile_trunc(t_token *t)
{
	int		outfile;
	t_token	*temp;

	temp = t;
	outfile = open(t->next->str[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		ft_dprintf(2, "%s, no directory or not permitted\n",
			t->next->str[0]);
		while (temp->type != 1 && temp->prev != t)
			temp = temp->prev;
		temp->exit_code = 1;
		t->next->type = 3;
		return ;
	}
	while (temp->type != 1 && temp->prev != t)
		temp = temp->prev;
	temp->outfile = outfile;
	t->next->type = 3;
}

static void	outfile_append(t_token *t)
{
	int		outfile;
	t_token	*temp;

	temp = t;
	outfile = open(t->next->str[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
	{
		ft_dprintf(2, "%s, no directory or not permitted\n",
			t->next->str[0]);
		while (temp->type != 1 && temp->prev != t)
			temp = temp->prev;
		temp->exit_code = 1;
		t->next->type = 3;
		return ;
	}
	while (temp->type != 1 && temp->prev != t)
		temp = temp->prev;
	temp->outfile = outfile;
	t->next->type = 3;
}

void	check_meta_char(t_shell *data, t_token *t)
{
	if (t->next == t || t->next == data->token)
		return ;
	if (strcmp(t->str[0], "<") == 0)
		infile_redirect(data, t);
	if (strcmp(t->str[0], ">") == 0)
		outfile_trunc(t);
	if (strcmp(t->str[0], ">>") == 0)
		outfile_append(t);
	if (strcmp(t->str[0], "<<") == 0)
		heredoc(data, t, t->next->str[0]);
}
