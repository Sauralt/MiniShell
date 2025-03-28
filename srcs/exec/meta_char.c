/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:15:33 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/28 12:27:48 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	infile_redirect(t_shell *data, int i)
{
	t_token	*t;
	int		j;
	int		infile;

	t = data->token;
	j = 0;
	while (j < i - data->del_num)
	{
		t = t->next;
		j++;
	}
	infile = open(t->next->str[0], O_RDONLY, 0644);
	if (infile == -1)
	{
		printf("%s, no file or directory or not permitted\n", t->prev->str[0]);
		return ;
	}
	t->prev->infile = infile;
}

static void	outfile_trunc(t_shell *data, int i)
{
	t_token	*t;
	int		j;
	int		outfile;

	t = data->token;
	j = 0;
	while (j < i - data->del_num)
	{
		t = t->next;
		j++;
	}
	outfile = open(t->next->str[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		printf("%s, no file or directory or not permitted\n", t->prev->str[0]);
		return ;
	}
	printf("%s\n", t->prev->str[0]);
	t->prev->outfile = outfile;
}

static void	outfile_append(t_shell *data, int i)
{
	t_token	*t;
	int		j;
	int		outfile;

	t = data->token;
	j = 0;
	while (j < i - data->del_num)
	{
		t = t->next;
		j++;
	}
	outfile = open(t->next->str[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
	{
		printf("%s, no file or directory or not permitted\n", t->prev->str[0]);
		return ;
	}
	t->prev->outfile = outfile;
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
		infile_redirect(data, i);
	if (strcmp(t->str[0], ">") == 0)
		outfile_trunc(data, i);
	if (strcmp(t->str[0], ">>") == 0)
		outfile_append(data, i);
}
