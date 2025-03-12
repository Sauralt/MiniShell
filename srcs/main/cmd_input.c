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

bool	is_builtin(char *line)
{
	char	**cmd;

	cmd = ft_split(line, ' ');
	if (ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "cd") == 0
		|| ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "export") == 0
		|| ft_strcmp(cmd[0], "unset") == 0 || ft_strcmp(cmd[0], "env") == 0
		|| ft_strcmp(cmd[0], "exit") == 0)
		return (true);
	return (false);
}

void	exec_cmd(char *line)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split(line, ' ');
	if (ft_strcmp("cd", cmd[0]) == 0)
		ft_cd(cmd[1]);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env();
	else if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "export") == 0 && cmd[1])
		ft_export(cmd[1]);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(cmd);
	// else if (ft_strcmp(cmd[0], "exit") == 0)
	// 	ft_exit(cmd);
	// free_str(cmd);
}
