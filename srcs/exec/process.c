/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:29:08 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/23 15:40:35 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_token *t, t_shell *data, int *fd)
{
	if (t->infile != STDIN_FILENO)
	{
		dup2(t->infile, STDIN_FILENO);
		close(t->infile);
	}
	if (t->outfile != STDOUT_FILENO)
	{
		dup2(t->outfile, STDOUT_FILENO);
		close(t->outfile);
	}
	if (t->next && strcmp(t->next->str[0], "|") == 0)
		dup2(fd[1], STDOUT_FILENO);
	ft_close(fd);
	exec_abs(t->str, data->env);
	perror("exec failed");
	exit(EXIT_FAILURE);
}

static int	exec_simple(t_shell *data, t_token *t)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (t->infile != STDIN_FILENO)
	{
		dup2(t->infile, STDIN_FILENO);
		close(t->infile);
	}
	if (t->outfile != STDOUT_FILENO)
	{
		dup2(t->outfile, STDOUT_FILENO);
		close(t->outfile);
	}
	if (pid == 0)
		exec_abs(t->str, data->env);
	waitpid(pid, NULL, 0);
	return (0);
}

int	exec(t_shell *data, t_token *t)
{
	int		fd[2];
	pid_t	pid;

	if (ft_strcmp(t->next->str[0], "|") != 0)
	{
		if (exec_simple(data, t) == 1)
			return (perror("fork"), 1);
		return (0);
	}
	if (pipe(fd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid < 0)
	{
		ft_close(fd);
		return (perror("fork"), 1);
	}
	if (pid == 0)
		child_process(t, data, fd);
	dup2(fd[0], STDIN_FILENO);
	ft_close(fd);
	waitpid(pid, NULL, 0);
	return (0);
}
