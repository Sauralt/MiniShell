/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:29:08 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/14 19:15:38 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_token *t, t_shell *data, int *fd)
{
	if (t->infile != STDIN_FILENO)
		dup2(t->infile, STDIN_FILENO);
	if (t->outfile != STDOUT_FILENO)
		dup2(t->outfile, STDOUT_FILENO);
	if (t->next && strcmp(t->next->str[0], "|") == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
	exec_abs(t->str, data->env);
	perror("exec failed");
	exit(EXIT_FAILURE);
}

int	exec(t_shell *data, t_token *t)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		child_process(t, data, fd);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, NULL, 0);
	return (0);
}
