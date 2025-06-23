/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:43:52 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/23 14:21:23 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_flag(t_shell *data, t_token *t)
{
	int		flag;
	t_token	*temp;

	flag = 0;
	temp = t;
	while (temp->next != data->token)
	{
		if (temp->str[0][0] == '|')
			flag = 1;
		temp = temp->next;
	}
	return (flag);
}

void	redirected(t_token *t)
{
	if (t->infile > STDIN_FILENO)
	{
		dup2(t->infile, STDIN_FILENO);
		close(t->infile);
	}
	if (t->outfile > STDOUT_FILENO)
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
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (data->prev_fd != -1)
			dup2(data->prev_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		if (data->prev_fd != -1)
			close(data->prev_fd);
		child_process(t, data, fd, original);
	}
	data->pids[data->l++] = pid;
	if (data->prev_fd != -1)
		close(data->prev_fd);
	data->prev_fd = fd[0];
	close(fd[1]);
}

void	close_files(t_shell *data)
{
	t_token	*t;

	t = data->token;
	if (t->infile > STDIN_FILENO)
		close(t->infile);
	if (t->outfile > STDOUT_FILENO)
		close(t->outfile);
	t = t->next;
	while (t != data->token)
	{
		if (t->infile > STDIN_FILENO)
			close(t->infile);
		if (t->outfile > STDOUT_FILENO)
			close(t->outfile);
		t = t->next;
	}
}
