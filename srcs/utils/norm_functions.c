/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:43:52 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/20 17:53:44 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_flag(t_shell *data, t_token *t)
{
	int	flag;

	flag = 0;
	while (t->next != data->token)
	{
		if (t->str[0][0] == '|')
			flag = 1;
		t = t->next;
	}
	t = t->next;
	return (flag);
}

void	redirected(t_token *t)
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
}

int	valid_path(t_shell *data, char *path)
{
	if (access(path, F_OK) != 0)
	{
		ft_dprintf(2, "%s: No such file or directory\n", path);
		free(path);
		data->exit_code = 127;
		return (127);
	}
	if (is_directory(path))
	{
		ft_dprintf(2, "%s: Is a directory\n", path);
		free(path);
		data->exit_code = 126;
		return (126);
	}
	if (access(path, X_OK) != 0)
	{
		ft_dprintf(2, "%s: Permission denied\n", path);
		free(path);
		data->exit_code = 126;
		return (126);
	}
	return (0);
}

void	ft_pipe(int *fd, int *original, t_shell *data, t_token *t)
{
	pid_t	pid;

	if (pipe(fd) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid < 0)
	{
		ft_close(fd);
		return (perror("fork"));
	}
	if (pid == 0 && t->type != 2)
		child_process(t, data, fd, original);
	if (t->next && ft_strcmp(t->next->str[0], "|") == 0)
		dup2(fd[0], STDIN_FILENO);
	ft_close(fd);
}

void	close_files(t_shell *data)
{
	t_token	*t;

	t = data->token;
	if (t->infile != STDIN_FILENO)
		close(t->infile);
	if (t->outfile != STDOUT_FILENO)
		close(t->outfile);
	t = t->next;
	while (t != data->token)
	{
		if (t->infile != STDIN_FILENO)
			close(t->infile);
		if (t->outfile != STDOUT_FILENO)
			close(t->outfile);
		t = t->next;
	}
}
