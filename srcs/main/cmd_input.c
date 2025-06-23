/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:01:42 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/06/19 16:26:24 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

bool	is_builtin(char *line)
{
	if (ft_strcmp(line, "echo") == 0 || ft_strcmp(line, "cd") == 0
		|| ft_strcmp(line, "pwd") == 0 || ft_strcmp(line, "export") == 0
		|| ft_strcmp(line, "unset") == 0 || ft_strcmp(line, "env") == 0
		|| ft_strcmp(line, "exit") == 0)
		return (true);
	return (false);
}

void	heredoc_norm(t_shell *data, t_token *t, int fd)
{
	if (t != data->token)
		infile_loop(t, 0, fd);
	else
		infile_loop(t, 1, fd);
}

void	exit_proc(t_shell *data, int exit_flag, int f, t_token *t)
{
	if (f == 1)
		ft_dprintf(2, "%s: command not found\n", t->str[0]);
	free_exit(data, exit_flag);
	if (exit_flag == -1 || exit_flag)
		exit_flag = 1;
	exit(exit_flag);
}

void	close_origin(int *original)
{
	close(original[0]);
	close(original[1]);
}
