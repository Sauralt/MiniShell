/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:06:28 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/06 16:31:01 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_exec(t_shell *data, t_token *t, int *fd)
{
	pid_t	pid;
	int		status;

	if (t->type == 0)
	{
		ft_dprintf(2, "%s: command not found\n", t->str[0]);
		data->exit_code = 127;
		return ;
	}
	if (t->type == 1)
	{
		if (pipe(fd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid < 0)
		{
			ft_close(fd);
			return (perror("fork"));
		}
		if (pid == 0 && t->type != 2)
			child_process(t, data, fd);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
	}
}

int	check_tok_order(t_shell *data)
{
	t_token	*t;

	t = data->token;
	if (t->type == 2)
	{
		data->exit_code = 2;
		return (ft_dprintf(2, "syntax error near unexpected token `%s'\n",
				t->str[0]), 2);
	}
	while (t->next != data->token)
	{
		if (t->type == 2 && t->next->type == 2)
		{
			data->exit_code = 2;
			return (ft_dprintf(2, "syntax error near unexpected token `%s'\n",
					t->next->str[0]), 2);
		}
		t = t->next;
	}
	if (t->type == 2)
	{
		data->exit_code = 2;
		return (ft_dprintf(2, "syntax error near unexpected token `newline'\n"),
			2);
	}
	return (0);
}

