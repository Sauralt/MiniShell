/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:29:08 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/09 11:48:17 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	check_access(char *path, char **cmd)
// {
// 	if (!access(cmd[0], X_OK))
// 	{
// 		free(path);
// 		ft_dprintf(2, "%s: no permissions\n", cmd[0]);
// 		exit(EXIT_FAILURE);
// 	}
// }

// int	exec_abs(t_shell *data, char **cmd, t_env *env, int i)
// {
// 	char	*path;
// 	char	**envp;

// 	if (cmd[0][0] == '\0')
// 		return (0);
// 	envp = make_env_str(env);
// 	path = find_path(cmd[0], env, i);
// 	if (!path)
// 	{
// 		ft_dprintf(2, "%s: command not found\n", cmd[0]);
// 		data->exit_code = 127;
// 		exit(EXIT_FAILURE);
// 	}
// 	check_access(path, cmd);
// 	if (execve(path, cmd, envp) == -1)
// 	{
// 		free(path);
// 		ft_dprintf(2, "%s: command not found\n", cmd[0]);
// 		data->exit_code = 127;
// 		exit(EXIT_FAILURE);
// 	}
// 	free(path);
// 	free_str(envp);
// 	return (0);
// }

#include <sys/stat.h>

int	is_directory(const char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (1);
	return (0);
}

int	exec_abs(t_shell *data, char **cmd, t_env *env, int i)
{
	char	*path;
	char	**envp;

	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
		exit(0);
	envp = make_env_str(env);
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
	{
		if (access(cmd[0], F_OK) != 0)
		{
			ft_dprintf(2, "%s: No such file or directory\n", cmd[0]);
			data->exit_code = 127;
			exit(127);
		}		if (access(cmd[0], F_OK) != 0)
		{
			ft_dprintf(2, "%s: No such file or directory\n", cmd[0]);
			data->exit_code = 127;
			exit(127);
			ft_dprintf(2, "%s: Is a directory\n", cmd[0]);
			data->exit_code = 126;
			exit(126);
		}
		if (access(cmd[0], X_OK) != 0)
		{
			ft_dprintf(2, "%s: Permission denied\n", cmd[0]);
			data->exit_code = 126;
			exit(126);
		}
		execve(cmd[0], cmd, envp);
		perror(cmd[0]);
		data->exit_code = 127;
		exit(127);
	}
	path = find_path(cmd[0], env, i);
	if (access(path, F_OK) != 0)
	{
		ft_dprintf(2, "%s: No such file or directory\n", path);
		free(path);
		data->exit_code = 127;
		exit(127);
	}
	if (is_directory(path))
	{
		ft_dprintf(2, "%s: Is a directory\n", path);
		free(path);
		data->exit_code = 126;
		exit(126);
	}
	if (access(path, X_OK) != 0)
	{
		ft_dprintf(2, "%s: Permission denied\n", path);
		free(path);
		data->exit_code = 126;
		exit(126);
	}
	execve(path, cmd, envp);
	perror(path);
	free(path);
	data->exit_code = 127;
	exit(127);
}

void	child_process(t_token *t, t_shell *data, int *fd)
{
	int	i;

	i = 0;
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
	if (t->next && ft_strcmp(t->next->str[0], "|") == 0
		&& ft_strncmp(t->next->next->str[0], "grep", 4) != 0)
		dup2(fd[1], STDOUT_FILENO);
	ft_close(fd);
	if (builtin(data, t) == 0)
		exit(EXIT_SUCCESS);
	else
		exec_abs(data, t->str, data->env, i);
	perror("exec failed\n");
	exit(EXIT_FAILURE);
}

int	exec_simple(t_shell *data, t_token *t)
{
	int		i;

	i = 0;
	g_signal_pid = fork();
	if (g_signal_pid == -1)
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
	if (g_signal_pid == 0)
		exec_abs(data, t->str, data->env, i);
	waitpid(g_signal_pid, NULL, 0);
	return (0);
}

void	close_dup(int original_stdin, int original_stdout)
{
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}
