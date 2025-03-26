/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:15:33 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/26 13:51:03 by cfleuret         ###   ########.fr       */
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
	while (j < i)
	{
		t = t->next;
		j++;
	}
	infile = open(t->prev->str[0], O_RDONLY, 0644);
	if (infile == -1)
	{
		printf("%s, no file or directory or not permitted\n", t->prev->str[0]);
		return ;
	}
	t->next->infile = infile;
}

void	check_meta_char(t_shell *data, int i)
{
	t_token	*t;
	int		j;

	j = 0;
	t = data->token;
	while (j < i)
	{
		t = t->next;
		j++;
	}
	if (strcmp(t->str[0], "<"))
		infile_redirect(data, i);
}
