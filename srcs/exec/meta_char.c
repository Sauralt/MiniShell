/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:15:33 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/11 15:46:35 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	infile_loop(t_token *t, int flag, int infile, int exit_code)
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
	if (temp->infile > 0)
		close(temp->infile);
	if (temp != t)
		temp->infile = infile;
	temp->invalid = ft_strdup(t->next->str[0]);
	temp->exit_code = exit_code;
}

static void	infile_redirect(t_shell *data, t_token *t)
{
	int		infile;
	int		error;

	infile = open(t->next->str[0], O_RDONLY, 0644);
	if (infile == -1)
	{
		if (access(t->next->str[0], F_OK) != 0)
			error = -1;
		else if (access(t->next->str[0], R_OK) != 0)
			error = -2;
		else if (is_directory(t->next->str[0]))
			error = -3;
		if (t != data->token)
			infile_loop(t, 0, error, 0);
		else
			infile_loop(t, 1, error, 0);
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
	int		error;
	t_token	*temp;

	temp = t;
	outfile = open(t->next->str[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		if (access(t->next->str[0], W_OK) != 0)
			error = -2;
		else if (is_directory(t->next->str[0]))
			error = -3;
		while (temp->type != 1 && temp->prev != t)
			temp = temp->prev;
		temp->outfile = error;
		t->next->type = 3;
		temp->invalid = ft_strdup(t->next->str[0]);
		return ;
	}
	while (temp->type != 1 && temp->prev != t)
		temp = temp->prev;
	if (temp->outfile > 1)
		close(temp->outfile);
	temp->outfile = outfile;
	t->next->type = 3;
}

static void	outfile_append(t_token *t)
{
	int		outfile;
	int		error;
	t_token	*temp;

	temp = t;
	outfile = open(t->next->str[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
	{
		if (access(t->next->str[0], W_OK) != 0)
			error = -2;
		else if (is_directory(t->next->str[0]))
			error = -3;
		while (temp->type != 1 && temp->prev != t)
			temp = temp->prev;
		temp->outfile = error;
		t->next->type = 3;
		temp->invalid = ft_strdup(t->next->str[0]);
		return ;
	}
	while (temp->type != 1 && temp->prev != t)
		temp = temp->prev;
	if (temp->outfile > 1)
		close(temp->outfile);
	temp->outfile = outfile;
	t->next->type = 3;
}

void	check_meta_char(t_shell *data, t_token *t)
{
	if (t->next == t || t->next == data->token)
		return ;
	if (ft_strcmp(t->str[0], "|") == 0)
		data->func_num++;
	if (ft_strcmp(t->str[0], "<") == 0)
		infile_redirect(data, t);
	if (ft_strcmp(t->str[0], ">") == 0)
		outfile_trunc(t);
	if (ft_strcmp(t->str[0], ">>") == 0)
		outfile_append(t);
	if (ft_strcmp(t->str[0], "<<") == 0)
		heredoc(data, t, t->next->str[0]);
}
