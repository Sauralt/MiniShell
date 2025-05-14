/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:29:08 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/14 17:12:19 by mgarsaul         ###   ########.fr       */
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

int	exec_abs(t_shell *data, char **cmd, t_env *env, int *original)
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
		exit(0);
	envp = make_env_str(env);
	path = find_path(cmd[0], env, i);
	exit_flag = valid_path(data, path);
	if (exit_flag != 0)
		exit(exit_flag);
	cmd[0] = find_absolute(cmd[0]);
	execve(path, cmd, envp);
	perror(path);
	free(path);
	data->exit_code = 127;
	exit(127);
}

void	child_process(t_token *t, t_shell *data, int *fd, int *original)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	redirected(t);
	if (t->next && ft_strcmp(t->next->str[0], "|") == 0)
		dup2(fd[1], STDOUT_FILENO);
	ft_close(fd);
	if (builtin(data, t, 2, original) == 0)
		exit(EXIT_SUCCESS);
	else
		exec_abs(data, t->str, data->env, original);
	perror("exec failed\n");
	exit(EXIT_FAILURE);
}

int	exec_simple(t_shell *data, t_token *t, int *original)
{
	int		status;

	g_signal_pid = fork();
	if (g_signal_pid == -1)
		return (1);
	redirected(t);
	if (g_signal_pid == 0)
		exec_abs(data, t->str, data->env, original);
	waitpid(g_signal_pid, &status, 0);
	if (WIFEXITED(status))
		t->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		t->exit_code = 128 + WTERMSIG(status);
	else
		t->exit_code = 1;
	return (0);
}

void	close_dup(int original_stdin, int original_stdout)
{
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}
