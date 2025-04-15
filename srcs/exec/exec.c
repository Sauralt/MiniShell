/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:58:48 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/15 13:08:52 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_abs(char **cmd, t_env *env)
{
	char	*path;
	char	**envp;

	envp = make_env_str(env);
	path = find_path(cmd[0], env);
	if (!path)
	{
		ft_dprintf(2, "%s: command not found\n", cmd[0]);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		ft_dprintf(2, "%s: command not found\n", cmd[0]);
		exit(EXIT_FAILURE);
	}
	free(path);
	free_str(envp);
	return (0);
}

static void	exec_built(t_shell *data, t_token *cmd)
{
	if (!cmd || !cmd->str)
		return ;
	if (ft_strncmp(cmd->str[0], "pwd", 4) == 0)
		ft_pwd(data);
	else if (ft_strncmp(cmd->str[0], "env", 4) == 0)
		ft_env(data);
	else if (ft_strncmp(cmd->str[0], "cd", 3) == 0 && cmd->next == cmd->prev)
		ft_cd(data, cmd);
	else if (ft_strncmp(cmd->str[0], "echo", 5) == 0)
		ft_echo(data, cmd);
	else if (ft_strncmp(cmd->str[0], "export", 7) == 0)
		ft_export(data, cmd);
	else if (ft_strncmp(cmd->str[0], "unset", 6) == 0)
		ft_unset(data, cmd);
	else if (ft_strncmp(cmd->str[0], "exit", 5) == 0)
		ft_exit(data, cmd);

}

static int	builtin(t_shell *data, t_token *cmd)
{
	while (cmd->type != 1)
		cmd = cmd->next;
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
	t_token	*t;
	int		original_stdin;
	int		original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	t = data->token;
	if (data->token->type == 2 && data->token->next == data->token)
		return (ft_dprintf(2, "syntax error\n"), 0);
	while (t->next != data->token)
	{
		if (t->type == 1)
		{
			if (builtin(data, data->token) == 1)
				exec(data, t);
		}
		t = t->next;
	}
	if (t->type == 1)
	{
		if (builtin(data, data->token) == 1)
			exec(data, t);
	}
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	return (0);
}
