/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:58:48 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/20 14:20:48 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_abs(char **cmd, t_env *env)
{
	char	*path;
	char	**envp;
	int		i;

	i = 0;
	envp = make_env_str(env);
	path = find_path(cmd[0], env, i);
	if (!path)
	{
		printf("%s: command not found\n", cmd[0]);
		return (1);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		printf("%s: command not found\n", cmd[0]);
		return (1);
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
		ft_cd(data, cmd->next->str[0]);
	else if (ft_strncmp(cmd->str[0], "echo", 5) == 0)
		ft_echo(cmd->next->str[0]);
	else if (ft_strncmp(cmd->str[0], "export", 7) == 0)
		ft_export(cmd->str[0]);
//	else if (ft_strncmp(cmd->str[0], "unset", 6) == 0)
//		ft_unset(cmd->next->str);
}

static int	builtin(t_shell *data, t_token *cmd)
{
	if (ft_strcmp(cmd->str[0], "echo") == 0 || ft_strcmp(cmd->str[0], "cd") == 0
		|| ft_strcmp(cmd->str[0], "pwd") == 0 || ft_strcmp(cmd->str[0], "export") == 0
		|| ft_strcmp(cmd->str[0], "unset") == 0 || ft_strcmp(cmd->str[0], "env") == 0
		|| ft_strcmp(cmd->str[0], "exit") == 0)
	{
		exec_built(data, cmd);
		return (0);
	}
	return (1);
}

int	proc(t_shell *data)
{
	if (data->token->type == 0)
	{
		printf("command not found : %s\n", data->token->str[0]);
		return (0);
	}
	if (data->token->type == 2 && data->token->next == data->token)
	{
		printf("parse error near \n");
		return (0);
	}
	if (builtin(data, data->token) == 1)
	{
		exec_abs(data->token->str, data->env);
		printf("temp\n");
	}
	return (0);
}
