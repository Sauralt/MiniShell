/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:29:08 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/05 14:30:27 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_access(char *path, char **cmd)
{
	if (!access(cmd[0], X_OK))
	{
		free(path);
		ft_dprintf(2, "%s: no permissions\n", cmd[0]);
		exit(EXIT_FAILURE);
	}
}

int	exec_abs(t_shell *data, char **cmd, t_env *env)
{
	char	*path;
	char	**envp;
	int		i;

	if (cmd[0][0] == '\0')
		return (0);
	i = 0;
	envp = make_env_str(env);
	path = find_path(cmd[0], env, i);
	if (!path)
	{
		ft_dprintf(2, "%s: command not found\n", cmd[0]);
		data->exit_code = 127;
		exit(EXIT_FAILURE);
	}
	check_access(path, cmd);
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		ft_dprintf(2, "%s: command not found\n", cmd[0]);
		data->exit_code = 127;
		exit(EXIT_FAILURE);
	}
	free(path);
	free_str(envp);
//	data->exit_code = 0;
	return (0);
}

void	child_process(t_token *t, t_shell *data, int *fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
	if (builtin(data, t) == 0)
		exit(EXIT_SUCCESS);
	else
		exec_abs(data, t->str, data->env);
	perror("exec failed\n");
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
		exec_abs(data, t->str, data->env);
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
