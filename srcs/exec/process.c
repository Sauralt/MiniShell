/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:58:48 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/18 17:11:46 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_abs(char *cmd, char **env)
{
	char	*path;
	int		i;

	if (env)
		path = find_path(cmd, env, i);
	if (!path)
	{
		ft_printf(2, "%s: command not found\n", cmd[0]);
		return (1);
	}
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		ft_printf(2, "%s: command not found\n", cmd[0]);
		return (1);
	}
	free(path);
	return (0);
}

static int	exec_built(t_shell *data, char *cmd)
{
	if (ft_strcmp("cd", cmd) == 0)
		return (ft_cd(data));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd(data));
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env();
	else if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(cmd);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd);
}

static int	builtin(t_shell *data, char *line)
{
	if (ft_strcmp(line, "echo") == 0 || ft_strcmp(line, "cd") == 0
		|| ft_strcmp(line, "pwd") == 0 || ft_strcmp(line, "export") == 0
		|| ft_strcmp(line, "unset") == 0 || ft_strcmp(line, "env") == 0
		|| ft_strcmp(line, "exit") == 0)
	{
		exec_built(data, line);
		return (0);
	}
	return (1);
}

int	proc(t_shell *data)
{
	if (data->token->type)
	{
		printf("command not found : %s\n", data->token->str);
		return (1);
	}
	if (data->token->type == 2 && data->token->next == data->token)
	{
		printf("parse error near \n");
		return (1);
	}
	if (builtin(data, data->token->str) == 1)
	{
		if (exec_abs(data->token->str, data->env) == 1)
			return (1);
	}
	return (0);
}
