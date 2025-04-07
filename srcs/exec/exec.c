/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:58:48 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/07 14:28:06 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	exec_abs(char **cmd, t_env *env)
// {
// 	char	*path;
// 	char	**envp;

// 	envp = make_env_str(env);
// 	path = find_path(cmd[0], env);
// 	if (!path)
// 	{
// 		ft_dprintf(2, "%s: command not found\n", cmd[0]);
// 		return (1);
// 	}
// 	if (execve(path, cmd, envp) == -1)
// 	{
// 		free(path);
// 		ft_dprintf(2, "%s: command not found\n", cmd[0]);
// 		return (1);
// 	}
// 	free(path);
// 	free_str(envp);
// 	return (0);
// }

int	exec_abs(char **cmd, t_env *env, t_shell *data)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**envp;

	path = find_path(cmd[0], env);
	if (!path)
	{
		ft_dprintf(2, "%s: command not found\n", cmd[0]);
		data->exit_code = 127;
		return (127);
	}
	envp = make_env_str(env);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		data->exit_code = 1;
		return (1);
	}
	else if (pid == 0)
	{
		if (execve(path, cmd, envp) == -1)
		{
			perror(cmd[0]);
			free(path);
			free_str(envp);
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
	}
	free(path);
	free_str(envp);
	return (data->exit_code);
}

static void	exec_built(t_shell *data, t_token *cmd)
{
	if (!cmd || !cmd->str)
		return ;
	if (ft_strncmp(cmd->str[0], "pwd", 4) == 0)
		data->exit_code = ft_pwd(data);
	else if (ft_strncmp(cmd->str[0], "env", 4) == 0)
		data->exit_code = ft_env(data);
	else if (ft_strncmp(cmd->str[0], "cd", 3) == 0 && cmd->next == cmd->prev)
		data->exit_code = ft_cd(data, cmd);
	else if (ft_strncmp(cmd->str[0], "echo", 5) == 0)
		data->exit_code = ft_echo(cmd);
	else if (ft_strncmp(cmd->str[0], "export", 7) == 0)
		data->exit_code = ft_export(data, cmd);
	else if (ft_strncmp(cmd->str[0], "unset", 6) == 0)
		data->exit_code = ft_unset(data, cmd);
	else if (ft_strncmp(cmd->str[0], "exit", 5) == 0)
		data->exit_code = ft_exit(data, cmd);
}

static int	builtin(t_shell *data, t_token *cmd)
{
	if (ft_strcmp(cmd->str[0], "echo") == 0
		|| ft_strcmp(cmd->str[0], "cd") == 0
		|| ft_strcmp(cmd->str[0], "pwd") == 0
		|| ft_strcmp(cmd->str[0], "export") == 0
		|| ft_strcmp(cmd->str[0], "unset") == 0
		|| ft_strcmp(cmd->str[0], "env") == 0
		|| ft_strcmp(cmd->str[0], "exit") == 0)
	{
		exec_built(data, cmd);
		return (0);
	}
	return (1);
}

int	proc(t_shell *data)
{
	pid_t	pid;

	if (data->token->type == 2 && data->token->next == data->token)
	{
		printf("syntax error\n");
		return (0);
	}
	if (builtin(data, data->token) == 1)
	{
		pid = fork();
		if (pid < 0)
			return (ft_dprintf(2, "fork: Resource unavailable"), 1);
		if (pid == 0)
			parent_process(data);
		else
			waitpid(pid, NULL, 0);
	}
	return (0);
}
