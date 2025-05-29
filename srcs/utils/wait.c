/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:03:28 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/29 19:19:03 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	waitall(t_shell *data, pid_t pid)
{
	int	status;
	int	flag;

	while (data->pipe_num != 0)
	{
		flag = waitpid(0, &status, 0);
		if (flag == pid)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
		}
		data->pipe_num--;
	}
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
