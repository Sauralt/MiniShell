/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-10 14:01:42 by mgarsaul          #+#    #+#             */
/*   Updated: 2025-03-10 14:01:42 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

bool	is_builtin(t_shell *data)
{
	char	**cmd;

	if (!data || !data->cmd || !data->cmd->str)
		return (false);
	cmd = ft_split(data->cmd->str, ' ');
	if (!cmd || !cmd[0])
	{
//		free_str(cmd);
		return (false);
	}
	if (ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "cd") == 0
		|| ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "export") == 0
		|| ft_strcmp(cmd[0], "unset") == 0 || ft_strcmp(cmd[0], "env") == 0
		|| ft_strcmp(cmd[0], "exit") == 0)
	{
//		free_str(cmd);
		return (true);
	}
///	free_str(cmd);
	return (false);
}

void	exec_cmd(t_shell *data)
{
	char	**cmd;

//	if (!data || !data->cmd || !data->cmd->str)
//		return ;

	cmd = ft_split(data->cmd->str, ' ');
//	if (!cmd || !cmd[0])
//	{
//		free_str(cmd);
//		return ;
	//}

	if (ft_strcmp(cmd[0], "cd") == 0 && !cmd[2])
		ft_cd(cmd[1], data);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env();
	else if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "export") == 0 && cmd[1])
		ft_export(cmd[1]);
	else if (ft_strcmp(cmd[0], "unset") == 0 && cmd[1])
	{
		char *args[2] = {cmd[1], NULL};
		ft_unset(args);
	}
//	else if (ft_strcmp(cmd[0], "exit") == 0)
//		ft_exit(cmd);

//	free_str(cmd);
}

bool	execution(t_shell *data)
{
	char	**cmd;

	if (!data || !data->cmd || !data->cmd->str)
		return (false);
	cmd = ft_split(data->cmd->str, ' ');
	if (!cmd)
		return (false);
	if (is_builtin(data))
	{
		exec_cmd(data);
//		free_str(cmd);
		return (false);
	}
//	free_str(cmd);
	return (true);
}
