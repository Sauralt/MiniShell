/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:58:48 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/19 16:13:46 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	exec_abs(char *cmd, t_env *env)
// {
// 	char	*path;
// 	char	**envp;
// 	char	**cmds;
// 	int		i;

// 	i = 0;

// 	cmds = ft_split(cmd, ' ');
// 	envp = make_env_str(env);
// 	path = find_path(cmds[0], env, i);
// 	if (!path)
// 	{
// 		printf("%s: command not found\n", cmd);
// 		return (1);
// 	}
// 	if (execve(path, cmds, envp) == -1)
// 	{
// 		free(path);
// 		printf("%s: command not found\n", cmd);
// 		return (1);
// 	}
// 	free(path);
// 	free(cmds);
// 	free_str(envp);
// 	return (0);
// }

static void	exec_built(t_shell *data, t_token *cmd)
{
	if (!cmd || !cmd->str)
		return ;

	if (ft_strncmp(cmd->str, "pwd", 4) == 0)
		ft_pwd(data);
	else if (ft_strncmp(cmd->str, "env", 4) == 0)
		ft_env(data);
	else if (ft_strncmp(cmd->str, "cd", 3) == 0 && cmd->next == cmd->prev)
		ft_cd(data, cmd->next->str);
	else if (ft_strncmp(cmd->str, "echo", 5) == 0)
		ft_echo(cmd->next->str);
	else if (ft_strncmp(cmd->str, "export", 7) == 0)
		ft_export(cmd->str);
//	else if (ft_strncmp(cmd->str, "unset", 6) == 0)
//		ft_unset(cmd->next->str);
}

static int	builtin(t_shell *data, t_token *cmd)
{
	if (ft_strcmp(cmd->str, "echo") == 0 || ft_strcmp(cmd->str, "cd") == 0
		|| ft_strcmp(cmd->str, "pwd") == 0 || ft_strcmp(cmd->str, "export") == 0
		|| ft_strcmp(cmd->str, "unset") == 0 || ft_strcmp(cmd->str, "env") == 0
		|| ft_strcmp(cmd->str, "exit") == 0)
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
		printf("command not found : %s\n", data->token->str);
		return (0);
	}
	if (data->token->type == 2 && data->token->next == data->token)
	{
		printf("parse error near \n");
		return (0);
	}
	if (builtin(data, data->token) == 1)
	{
		//exec_abs(data->token->str, data->env);
		printf("temp\n");
	}
	return (0);
}
