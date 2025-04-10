/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:29:08 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/10 18:07:29 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	parent_process(t_shell *t, int *fd)
// {
// 	if (strcmp(t->token->next->str[0], "|") == 0)
// 	{
// 		t->token->outfile = fd[0];
// 		t->token->next->next->infile = fd[0];
// 		t->token->next->next->outfile = fd[1];
// 	}
// 	else
// 	{
// 		dup2(t->token->infile, 0);
// 		dup2(t->token->outfile, 1);
// 		exec_abs(t->token->str, t->env);
// 	}
// }

void	parent_process(t_shell *t)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], t->token->next->next->infile);
		exec_abs(t->token->str, t->env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], t->token->next->next);
		waitpid(pid, NULL, 0);
	}
}

int	exec(t_shell *data, t_shell *t)
{
	while (t->token->type != 1)
		t->token = t->token->next;
	while (t->token->type == 1 || t->token->type == 2
		|| t->token->next == data->token)
	{
		if (t->token->type == 1)
		{
			parent_process(t);
		}
		t->token = t->token->next;
	}
	return (0);
}

// int	exec(t_shell *data, t_shell *t)
// {
// 	pid_t	pid;
// 	int		fd[2];

// 	while (t->token->type != 1)
// 		t->token = t->token->next;
// 	while (t->token->type == 1 || t->token->type == 2)
// 	{
// 		if (pipe(fd) == -1)
// 			return (ft_dprintf(2, "pipe: Resource unavailable"), 1);
// 		pid = fork();
// 		if (pid < 0)
// 			return (ft_dprintf(2, "fork: Resource unavailable"), 1);
// 		if (pid == 0)
// 			parent_process(data);
// 		else
// 			waitpid(pid, NULL, 0);
// 		t->token = t->token->next;
// 		if (t->token == data->token)
// 			break ;
// 	}
// 	return (0);
// }
