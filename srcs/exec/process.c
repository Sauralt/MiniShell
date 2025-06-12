/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:29:08 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/12 13:03:50 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(const char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (1);
	return (0);
}

void	exec_abs(t_shell *data, char **cmd, t_env *env, int *original)
{
	char	*path;
	char	**envp;
	int		exit_flag;
	int		i;

	close(original[0]);
	close(original[1]);
	close_files(data);
	i = 0;
	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
		exit_proc(data, 0, 0, data->token);
	envp = make_env_str(env);
	path = find_path(cmd[0], env, i);
	exit_flag = valid_path(data, path);
	if (exit_flag != 0)
	{
		free_str(envp);
		exit_proc(data, exit_flag, 0, data->token);
	}
	cmd[0] = find_absolute(cmd[0]);
	execve(path, cmd, envp);
	perror(path);
	free(path);
	free_str(envp);
	exit_proc(data, 127, 0, data->token);
}

void	child_process(t_token *t, t_shell *data, int *fd, int *original)
{
	if (t->type == 0)
	{
		ft_dprintf(2, "%s: command not found\n", t->str[0]);
		close(original[0]);
		close(original[1]);
		ft_close(fd);
		free_exit(data, 1);
		exit(127);
	}
	if (t->infile < 0 || t->outfile < 0)
	{
		if (t->infile == -1)
			ft_dprintf(2, "%s: No such file or directory\n", t->invalid);
		if (t->infile == -2 || t->outfile == -2)
			ft_dprintf(2, "%s: Permission denied\n", t->invalid);
		if (t->infile == -3 || t->outfile == -3)
			ft_dprintf(2, "%s: Is a directory\n", t->invalid);
		ft_close(fd);
		free_exec_simple(data, t, original, 1);
	}
	redirected(t);
	ft_close(fd);
	if (builtin(data, t, original, 1) == 0)
		exit(EXIT_SUCCESS);
	else
		exec_abs(data, t->str, data->env, original);
	perror("exec failed\n");
	exit(EXIT_FAILURE);
}

int	exec_simple(t_shell *data, t_token *t, int *original, int flag)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (t->type == 0)
			free_exec_simple(data, t, original, 127);
		signal(SIGQUIT, SIG_DFL);
		if (data->prev_fd != -1)
		{
			dup2(data->prev_fd, STDIN_FILENO);
			close(data->prev_fd);
		}
		if (t->infile < 0 || t->outfile < 1)
		{
			if (t->infile == -1)
				ft_dprintf(2, "%s: No such file or directory\n", t->invalid);
			if (t->infile == -2 || t->outfile == -2)
				ft_dprintf(2, "%s: Permission denied\n", t->invalid);
			if (t->infile == -3 || t->outfile == -3)
				ft_dprintf(2, "%s: Is a directory\n", t->invalid);
			if (flag == 0)
				free_exec_simple(data, t, original, -1);
			else
				free_exec_simple(data, t, original, 1);
		}
		redirected(t);
		exec_abs(data, t->str, data->env, original);
	}
	if (flag == 0)
		ft_waitpid(pid, t);
	else
		data->pids[data->l++] = pid;
	return (0);
}

void	close_dup(int original_stdin, int original_stdout)
{
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}
