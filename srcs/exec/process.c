/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:29:08 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/29 15:28:04 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_token *t, t_shell *data, int *fd)
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

int	exec_simple(t_shell *data, t_token *t)
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

void	close_dup(int original_stdin, int original_stdout)
{
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}

// int	exec(t_shell *data, t_token *t)
// {
// 	int		fd[2];
// 	pid_t	pid;

// 	if (ft_strcmp(t->next->str[0], "|") != 0)
// 	{
// 		if (exec_simple(data, t) == 1)
// 			return (perror("fork"), 1);
// 		return (0);
// 	}
// 	if (pipe(fd) == -1)
// 		return (perror("pipe"), 1);
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		ft_close(fd);
// 		return (perror("fork"), 1);
// 	}
// 	if (pid == 0)
// 		child_process(t, data, fd);
// 	dup2(fd[0], STDIN_FILENO);
// 	ft_close(fd);
// 	waitpid(pid, NULL, 0);
// 	return (0);
// }
