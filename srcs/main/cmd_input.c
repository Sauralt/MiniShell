/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:01:42 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/05/27 17:02:37 by mgarsaul         ###   ########.fr       */
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

void	ft_waitpid(pid_t pid, t_token *cmd)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		cmd->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		cmd->exit_code = 128 + WTERMSIG(status);
	else
		cmd->exit_code = 1;
}

void	heredoc_norm(t_shell *data, t_token *t, int fd)
{
	if (t != data->token)
		infile_loop(t, 0, fd, 0);
	else
		infile_loop(t, 1, fd, 0);
}

void	exit_proc(t_shell *data, int exit_flag)
{
	free_exit(data);
	exit(exit_flag);
}

void	close_origin(int *original)
{
	close(original[0]);
	close(original[1]);
}
