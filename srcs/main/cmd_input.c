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

bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
	{
		printf("builtin\n");
		return (true);
	}
	return (false);
}

void	exec_cmd(char *line)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split(line, ' ');
	if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd();
/*	else if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env();
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd);
	free_str(cmd);*/
}
